#include "RenderDevice.h"

#include "Mesh.h"
#include "Shader.h"
#include "VideoManager.h"

#include "../Components/Camera.h"
#include "../Core/LogUtil.h"
#include "../Engine/Settings.h"

#include "../../Base/Base.h"
using namespace base;

#include <algorithm>

namespace orb
{
	void RenderDevice::addRenderable(Renderable* renderable)
	{
		m_renderables.push_back(renderable);
		m_isDirty = true;
	}

	void RenderDevice::updateRenderable(Renderable* renderable)
	{
		deleteRenderable(renderable);
		addRenderable(renderable);
		m_isDirty = true;
	}

	void RenderDevice::deleteRenderable(Renderable* renderable)
	{
		m_renderables.erase(std::remove(m_renderables.begin(), m_renderables.end(), renderable), m_renderables.end());
		m_isDirty = true;
	}

	void RenderDevice::clear()
	{
		m_renderables.clear();
	}

	void RenderDevice::render()
	{
		computeBatches();

		prepareRendering();

		for (unsigned i = 0; i < m_batches.size(); i++)
			m_batches[i].render();

		finishRendering();

#ifdef ORBIS_DEBUG_RENDERDEVICE
		LogUtil::logMessage("Number of draw calls: %d", m_batches.size());
#endif
	}

	void RenderDevice::computeBatches()
	{
		if (m_isDirty)
		{
			std::vector<std::vector<Renderable*>> grouping
				= ContainerUtil::group(m_renderables, Renderable::areBatchEqual);

			m_batches.clear();
			for (unsigned int i = 0; i < grouping.size(); i++)
			{
				m_batches.push_back(RenderBatch());
				m_batches[i].setRenderables(grouping[i]);
			}

			m_isDirty = false;
		}
	}

	void RenderDevice::prepareRendering()
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void RenderDevice::finishRendering()
	{
		glDisable(GL_BLEND);
	}

	void RenderBatch::setRenderables(std::vector<Renderable*> renderables)
	{
		m_renderables = renderables;
		m_isDirty = true;
	}

	void RenderBatch::render()
	{
		Exception::assert(Camera::getInstance() != NULL, "No camera is attached to the level");

		calculateIndices();
		calculateVertices();

		// init batch prototype
		Renderable* prototype = getRenderables()[0];
		if (prototype->getMaterial()->getTexture() != NULL)
			prototype->getMaterial()->getTexture()->bind();
		prototype->getMaterial()->getShader()->use();
		prototype->getMaterial()->prepareShaderVariables();

		// set shader's position variable
		unsigned int stride = prototype->getMesh()->getVertexData()->size();
		int positionAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vPosition");
		glEnableVertexAttribArray(positionAttribLocation);
		glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, &(m_vertices[0]));

		// set texture coordinate shader variable
		if (prototype->getMaterial()->getTexture() != NULL) {
			int texCoordAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vTexCoord");
			glEnableVertexAttribArray(texCoordAttribLocation);
			glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, &(m_vertices[2]));
		}

		// set vertex color shader variable
		if (prototype->getMesh()->isVertexColored()) {
			int vertexColorAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vVertexColor");
			glEnableVertexAttribArray(vertexColorAttribLocation);
			glVertexAttribPointer(vertexColorAttribLocation, 4, GL_FLOAT, GL_FALSE, stride, &(m_vertices[4]));
		}

		// draw the batch
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, &(m_indices[0]));

		// cleanup
		prototype->getMaterial()->getShader()->unuse();
		if (prototype->getMaterial()->getTexture() != NULL)
			glDisableVertexAttribArray(prototype->getMaterial()->getShader()->getAttributeLocation("a_vTexCoord"));
		glDisableVertexAttribArray(positionAttribLocation);
	}

	void RenderBatch::calculateIndices()
	{
		if (m_isDirty)
		{
			m_indices.clear();
			reserveIndexMemory();

			unsigned int offset = 0;
			for (unsigned int i = 0; i < m_renderables.size(); i++)
			{
				std::vector<GLushort> newIndices;
				m_renderables[i]->getMesh()->computeIndices(newIndices, offset);

				m_indices.insert(m_indices.end(), newIndices.begin(), newIndices.end());

				offset += m_renderables[i]->getMesh()->getNumVertices();
			}

			m_isDirty = false;
		}
	}

	void RenderBatch::reserveIndexMemory()
	{
		// reserve memory
		unsigned int indexArrayCount = 0;
		for (unsigned int i = 0; i < m_renderables.size(); i++) {
			indexArrayCount += m_renderables[i]->getMesh()->getIndices()->size();
		}
		m_indices.reserve(indexArrayCount);
	}

	void RenderBatch::calculateVertices()
	{
		m_vertices.clear();
		reserveVertexMemory();

		unsigned int vertexArrayCount = 0;
		for (unsigned int i = 0; i < m_renderables.size(); i++) {
			vertexArrayCount += m_renderables[i]->getMesh()->getVertexData()->size();
		}
		m_vertices.reserve(vertexArrayCount); 

		for (unsigned int i = 0; i < m_renderables.size(); i++)
		{
			std::vector<float> vertices = computeTransformedVertices(m_renderables[i]);
			m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
		}
	}

	void RenderBatch::reserveVertexMemory()
	{
		unsigned int vertexArrayCount = 0;
		for (unsigned int i = 0; i < m_renderables.size(); i++) {
			vertexArrayCount += m_renderables[i]->getMesh()->getVertexData()->size();
		}
		m_vertices.reserve(vertexArrayCount);
	}

	std::vector<float> RenderBatch::computeTransformedVertices(Renderable* renderable)
	{
		// compute mvp matrix
		Transform* transform = renderable->getTransform();
		Camera* cam = Camera::getInstance();
		Matrix3 camMatrix = cam->getCamMatrix(transform->transformSpace);
		Matrix3 mvpMatrix = camMatrix * transform->getModelMatrix();

		// compute transformed vertex data
		Mesh* mesh = renderable->getMesh();
		Texture* tex = renderable->getMaterial()->getTexture();
		std::vector<float> data = *mesh->getVertexData();
		for (unsigned int i = 0; i < mesh->getNumVertices(); i++)
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
