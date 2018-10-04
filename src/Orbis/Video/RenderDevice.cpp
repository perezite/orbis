#include "RenderDevice.h"

#include "Mesh.h"
#include "Shader.h"
#include "VideoManager.h"

#include "../Components/Camera.h"
#include "../Core/LogUtil.h"
#include "../Engine/Settings.h"

#include <algorithm>

namespace
{
	using namespace orb;

	std::vector<std::vector<Renderable*>> groupByBatches(std::vector<Renderable*> renderables)
	{
		std::vector<Renderable*> list = renderables;
		std::vector<std::vector<Renderable*>> grouping;

		while (list.size() > 0)
		{
			Renderable* proto = list[0];
			std::vector<Renderable*> group;

			for (unsigned int i = 0; i < list.size(); i++)
			{
				if (list[i]->isBatchableWith(proto))
				{
					group.push_back(list[i]);
					list.erase(list.begin() + i);
					i = i - 1;
				}
			}

			grouping.push_back(group);
		}

		return grouping;
	}
}

namespace orb
{
	void RenderDevice::addRenderable(Renderable* renderable)
	{
		m_renderables.push_back(renderable);
	}

	void RenderDevice::updateRenderable(Renderable* renderable)
	{
		deleteRenderable(renderable);
		addRenderable(renderable);
	}

	void RenderDevice::deleteRenderable(Renderable* renderable)
	{
		m_renderables.erase(std::remove(m_renderables.begin(), m_renderables.end(), renderable), m_renderables.end());
	}

	void RenderDevice::clear()
	{
		m_renderables.clear();
	}

	void RenderDevice::render()
	{
		computeBatches();

		for (unsigned i = 0; i < m_batches.size(); i++)
			m_batches[i].render();

		#ifdef ORBIS_DEBUG_RENDERDEVICE
			LogUtil::logMessage("Number of draw calls: %d", m_batches.size());
		#endif
	}

	void RenderDevice::computeBatches()
	{
		std::vector<std::vector<Renderable*>> grouping 
			= groupByBatches(m_renderables);
		
		m_batches.clear();
		for (unsigned int i = 0; i < grouping.size(); i++)
		{
			m_batches.push_back(RenderBatch());
			m_batches[i].setRenderables(grouping[i]);
		}
	}

	void RenderBatch::setRenderables(std::vector<Renderable*> renderables)
	{
		m_renderables = renderables;
		calculateIndexes();
		calculateVertexes();
	}

	void RenderBatch::render()
	{
		// set states
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// init batch prototype
		Renderable* prototype = getRenderables()[0];
		if (prototype->getMaterial()->getTexture() != NULL)
			prototype->getMaterial()->getTexture()->bind();
		prototype->getMaterial()->getShader()->use();
		prototype->getMaterial()->prepareShaderVariables();

		// set shader's position variable
		unsigned int stride = prototype->getMesh()->getVertexes2()->size();
		int positionAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vPosition");
		glEnableVertexAttribArray(positionAttribLocation);
		glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, &(m_vertexes[0]));

		// set texture coordinate shader variable
		if (prototype->getMaterial()->getTexture() != NULL) {
			int texCoordAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vTexCoord");
			glEnableVertexAttribArray(texCoordAttribLocation);
			glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, &(m_vertexes[2]));
		}

		// set vertex color shader variable
		if (prototype->getMesh()->isVertexColored()) {
			int vertexColorAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vVertexColor");
			glEnableVertexAttribArray(vertexColorAttribLocation);
			glVertexAttribPointer(vertexColorAttribLocation, 4, GL_FLOAT, GL_FALSE, stride, &(m_vertexes[4]));
		}

		// draw the batch
		glDrawElements(GL_TRIANGLES, m_indexes.size(), GL_UNSIGNED_SHORT, &(m_indexes[0]));

		// cleanup
		prototype->getMaterial()->getShader()->unuse();
		if (prototype->getMaterial()->getTexture() != NULL)
			glDisableVertexAttribArray(prototype->getMaterial()->getShader()->getAttributeLocation("a_vTexCoord"));
		glDisableVertexAttribArray(positionAttribLocation);
		glDisable(GL_BLEND);
	}

	void RenderBatch::calculateIndexes()
	{
		m_indexes.clear();

		unsigned int offset = 0;
		for (unsigned int i = 0; i < m_renderables.size(); i++)
		{
			std::vector<GLushort> newIndexes = m_renderables[i]->getMesh()->getIndexes();
			for (unsigned int i = 0; i < newIndexes.size(); i++)
				newIndexes[i] += offset;

			m_indexes.insert(m_indexes.end(), newIndexes.begin(), newIndexes.end());

			offset += m_renderables[i]->getMesh()->getNumVertexes();
		}
	}

	void RenderBatch::calculateVertexes()
	{
		m_vertexes.clear();

		for (unsigned int i = 0; i < m_renderables.size(); i++)
		{
			std::vector<GLfloat> newVertexes = m_renderables[i]->getMesh()->getVertexes();
			std::vector<float> vertexes = computeTransformedVertexes(m_renderables[i]);
			m_vertexes.insert(m_vertexes.end(), vertexes.begin(), vertexes.end());
		}
	}

	std::vector<float> RenderBatch::computeTransformedVertexes(Renderable* renderable)
	{
		// compute mvp matrix
		Transform* transform = renderable->getTransform();
		Matrix3 camMatrix = Camera::getInstance()->calcCamMatrix(transform->transformSpace);
		Matrix3 mvpMatrix = camMatrix * transform->getModelMatrix();

		// compute transformed vertex data
		Mesh* mesh = renderable->getMesh();
		Texture* tex = renderable->getMaterial()->getTexture();
		std::vector<float> data = mesh->getVertexes();
		for (unsigned int i = 0; i < mesh->getNumVertexes(); i++)
		{
			unsigned int start = i * mesh->getVertexCount();
			Vector2D pos = mvpMatrix * Vector2D(data[start + 0], data[start + 1]);
			data[start + 0] = pos.x; data[start + 1] = pos.y;
			if (tex) {
				Vector2D uvCoord = tex->mapUVCoord(Vector2D(data[start + 2], data[start + 3]));
				data[start + 2] = uvCoord.x; data[start + 3] = uvCoord.y;
			}
		}

		return data;
	}
}