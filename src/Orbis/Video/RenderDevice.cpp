#include "RenderDevice.h"

#include "Mesh.h"
#include "Shader.h"
#include "VideoManager.h"

#include "../Components/Camera.h"
#include "../Core/LogUtil.h"
#include "../Engine/Settings.h"

#include <algorithm>

namespace orb
{
	void RenderDevice::addRenderable(Renderable* renderable)
	{
		int position = findFirstIndexInBatch(renderable);
		m_renderables.insert(m_renderables.begin() + position, renderable);
		m_areIndexesDirty = true;
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
		#ifdef ORBIS_DEBUG_RENDERDEVICE
			int count = 0;
		#endif 

		// set states
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// updateLevel arrays
		updateIndexArray();
		updateVertexArray();
		updateBatches();

		// skip if nothing to render
		if (m_vertexes.size() == 0)
			return;

		for (unsigned int i = 0; i < m_batches.size(); i++)
		{
			unsigned int batchBegin = m_batches[i].min;
			unsigned int batchCount = m_batches[i].diff() + 1;
			unsigned int vaoStartIndex = computeVaoStartIndex(i, m_batches);
			unsigned int iboStartIndex = computeIboStartIndex(i, m_batches);
			Renderable* prototype = m_renderables[batchBegin];

			// init batch prototype
			if (prototype->getMaterial()->getTexture() != NULL)
				prototype->getMaterial()->getTexture()->bind();
			prototype->getMaterial()->getShader()->use();
			prototype->getMaterial()->prepareShaderVariables();

			// set position shader variable
			unsigned int stride = prototype->getMesh()->getVertexes()->size();
			int positionAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vPosition");
			glEnableVertexAttribArray(positionAttribLocation);
			glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, &(m_vertexes[vaoStartIndex]));

			// set texture coordinate shader variable
			if (prototype->getMaterial()->getTexture() != NULL) {
				int texCoordAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vTexCoord");
				glEnableVertexAttribArray(texCoordAttribLocation);
				glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, &(m_vertexes[vaoStartIndex + 2]));
			}

			// set vertex color shader variable
			if (prototype->getMesh()->isVertexColored()) {
				int vertexColorAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vVertexColor");
				glEnableVertexAttribArray(vertexColorAttribLocation);
				glVertexAttribPointer(vertexColorAttribLocation, 4, GL_FLOAT, GL_FALSE, stride, &(m_vertexes[vaoStartIndex + 4]));
			}

			// draw batched
			glDrawElements(GL_TRIANGLES, batchCount * prototype->getMesh()->getIndexes()->size(), GL_UNSIGNED_SHORT, &m_indexes[iboStartIndex]);

			// cleanup
			prototype->getMaterial()->getShader()->unuse();
			if (prototype->getMaterial()->getTexture() != NULL)
				glDisableVertexAttribArray(prototype->getMaterial()->getShader()->getAttributeLocation("a_vTexCoord"));
			if (prototype->getMesh()->isVertexColored())
				glDisableVertexAttribArray(prototype->getMaterial()->getShader()->getAttributeLocation("a_vVertexColor"));
			glDisableVertexAttribArray(positionAttribLocation);

			#ifdef ORBIS_DEBUG_RENDERDEVICE
				count++;
			#endif 
		}

		#ifdef ORBIS_DEBUG_RENDERDEVICE
			LogUtil::logMessage("Number of draw calls: %d", count);
		#endif 

		// cleanup
		glDisable(GL_BLEND);
	}

	void RenderDevice::updateVertexArray()
	{
		Matrix3 worldCamMatrix = Camera::getInstance()->calcCamMatrix(TransformSpace::World);
		Matrix3 localCamMatrix = Camera::getInstance()->calcCamMatrix(TransformSpace::Camera);

		m_vertexes.clear();
		reserveVertexArray();

		for (unsigned int i = 0; i < m_renderables.size(); i++)
		{
			Transform* transform = m_renderables[i]->getTransform();
			bool isWorldSpace = transform->transformSpace == TransformSpace::World ? true : false;
			Matrix3 mvpMatrix = (isWorldSpace ? worldCamMatrix : localCamMatrix) * transform->getModelMatrix();
			insertIntoVertexArray(m_renderables[i], mvpMatrix);
		}
	}

	void RenderDevice::insertIntoVertexArray(Renderable* const renderable, Matrix3& mvpMatrix)
	{
		Mesh* mesh = renderable->getMesh();
		Texture* tex = renderable->getMaterial()->getTexture();

		// apply transformation on mesh data
		std::vector<GLfloat> data = *mesh->getVertexes();
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

		m_vertexes.insert(m_vertexes.end(), data.begin(), data.end());
	}

	void RenderDevice::reserveVertexArray()
	{
		unsigned int vertexArrayCount = 0;
		for (unsigned int i = 0; i < m_renderables.size(); i++) {
			vertexArrayCount += m_renderables[i]->getMesh()->getVertexes()->size();
		}

		m_vertexes.reserve(vertexArrayCount);
	}

	void RenderDevice::updateIndexArray()
	{
		if (m_areIndexesDirty)
		{
			m_indexes.clear();
			reserveIndexArray();

			GLushort offset = 0;
			for (unsigned int i = 0; i < m_renderables.size(); i++)
			{
				insertIntoIndexArray(i, offset);
			}

			m_areIndexesDirty = false;
		}
	}

	void RenderDevice::insertIntoIndexArray(unsigned int index, unsigned short& offset)
	{
		// reset value offet when switching batch
		if (index == 0 || !m_renderables[index]->isBatchableWith(m_renderables[index - 1]))
			offset = 0;

		Mesh* mesh = m_renderables[index]->getMesh();
		for (unsigned int j = 0; j < mesh->getIndexes()->size(); j++)
		{
			GLushort value = offset + mesh->getIndexes()->at(j);
			m_indexes.insert(m_indexes.end(), value);
		}

		offset += mesh->getNumVertexes();
	}

	void RenderDevice::reserveIndexArray()
	{
		unsigned int count = 0;
		for (unsigned int i = 0; i < m_renderables.size(); i++)
			count += m_renderables[i]->getMesh()->getIndexes()->size();

		m_indexes.reserve(count);
	}

	unsigned int RenderDevice::computeVaoStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches)
	{
		unsigned int startIndex = 0;

		for (unsigned int i = 0; i < batchIndex; i++)
		{
			unsigned int begin = batches[i].min;
			unsigned int batchCount = batches[i].diff() + 1;
			startIndex += m_renderables[begin]->getMesh()->getVertexes()->size() * batchCount;
		}

		return startIndex;
	}

	unsigned int RenderDevice::computeIboStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches)
	{
		unsigned int startIndex = 0;

		for (unsigned int i = 0; i < batchIndex; i++)
		{
			unsigned int begin = batches[i].min;
			unsigned int batchCount = batches[i].diff() + 1;
			startIndex += m_renderables[begin]->getMesh()->getIndexes()->size() * batchCount;
		}

		return startIndex;
	}

	void RenderDevice::updateBatches()
	{
		m_batches.clear();
		int begin = 0;
		int current = 0;
		int last = m_renderables.size();

		while (current < last)
		{
			while (current < last && m_renderables[begin]->isBatchableWith(m_renderables[current]))
				current++;

			m_batches.push_back(BatchRange(begin, current - 1));
			begin = current;

			if (current == last)
				break;
		}
	}

	int RenderDevice::findFirstIndexInBatch(Renderable* renderable)
	{
		for (unsigned int i = 0; i < m_renderables.size(); i++)
		{
			if (renderable->isBatchableWith(m_renderables[i]))
				return i;
		}

		return m_renderables.size();
	}
}