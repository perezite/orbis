#include "RenderDevice.h"

#ifdef OLD_STUFF

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
		m_isIndexArrayDirty = true;
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

		// skip if nothing to render
		if (m_vertexArray.size() == 0)
			return;

		// render batched
		std::vector<BatchRange> batches = computeBatches();
		for (unsigned int i = 0; i < batches.size(); i++)
		{
			unsigned int batchBegin = batches[i].min;
			unsigned int batchCount = batches[i].diff() + 1;
			unsigned int vaoStartIndex = computeVaoStartIndex(i, batches);
			unsigned int iboStartIndex = computeIboStartIndex(i, batches);
			Renderable* prototype = m_renderables[batchBegin];

			// init batch prototype
			if (prototype->getMaterial()->getTexture() != NULL)
				prototype->getMaterial()->getTexture()->bind();
			prototype->getMaterial()->getShader()->use();
			prototype->getMaterial()->prepareShaderVariables();

			// set position shader variable
			unsigned int stride = prototype->getMesh()->getVertexData()->size();
			int positionAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vPosition");
			glEnableVertexAttribArray(positionAttribLocation);
			glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, &(m_vertexArray[vaoStartIndex]));

			// set texture coordinate shader variable
			if (prototype->getMaterial()->getTexture() != NULL) {
				int texCoordAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vTexCoord");
				glEnableVertexAttribArray(texCoordAttribLocation);
				glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, &(m_vertexArray[vaoStartIndex + 2]));
			}

			// set vertex color shader variable
			if (prototype->getMesh()->isVertexColored()) {
				int vertexColorAttribLocation = prototype->getMaterial()->getShader()->getAttributeLocation("a_vVertexColor");
				glEnableVertexAttribArray(vertexColorAttribLocation);
				glVertexAttribPointer(vertexColorAttribLocation, 4, GL_FLOAT, GL_FALSE, stride, &(m_vertexArray[vaoStartIndex + 4]));
			}

			// draw batched
			glDrawElements(GL_TRIANGLES, batchCount * prototype->getMesh()->getIndices()->size(), GL_UNSIGNED_SHORT, &m_indexArray[iboStartIndex]);

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

		m_vertexArray.clear();
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
		std::vector<GLfloat> data = *mesh->getVertexData();
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

		m_vertexArray.insert(m_vertexArray.end(), data.begin(), data.end());
	}

	void RenderDevice::reserveVertexArray()
	{
		unsigned int vertexArrayCount = 0;
		for (unsigned int i = 0; i < m_renderables.size(); i++) {
			vertexArrayCount += m_renderables[i]->getMesh()->getVertexData()->size();
		}

		m_vertexArray.reserve(vertexArrayCount);
	}

	void RenderDevice::updateIndexArray()
	{
		if (m_isIndexArrayDirty)
		{
			m_indexArray.clear();
			reserveIndexArray();

			GLushort offset = 0;
			for (unsigned int i = 0; i < m_renderables.size(); i++)
			{
				insertIntoIndexArray(i, offset);
			}

			m_isIndexArrayDirty = false;
		}
	}

	void RenderDevice::insertIntoIndexArray(unsigned int index, unsigned short& offset)
	{
		// reset value offet when switching batch
		if (index == 0 || !m_renderables[index]->isBatchEqualTo(m_renderables[index - 1]))
			offset = 0;

		Mesh* mesh = m_renderables[index]->getMesh();
		for (unsigned int j = 0; j < mesh->getIndices()->size(); j++)
		{
			GLushort value = offset + mesh->getIndices()->at(j);
			m_indexArray.insert(m_indexArray.end(), value);
		}

		offset += mesh->getNumVertices();
	}

	void RenderDevice::reserveIndexArray()
	{
		unsigned int count = 0;
		for (unsigned int i = 0; i < m_renderables.size(); i++)
			count += m_renderables[i]->getMesh()->getIndices()->size();

		m_indexArray.reserve(count);
	}

	unsigned int RenderDevice::computeVaoStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches)
	{
		unsigned int startIndex = 0;

		for (unsigned int i = 0; i < batchIndex; i++)
		{
			unsigned int begin = batches[i].min;
			unsigned int batchCount = batches[i].diff() + 1;
			startIndex += m_renderables[begin]->getMesh()->getVertexData()->size() * batchCount;
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
			startIndex += m_renderables[begin]->getMesh()->getIndices()->size() * batchCount;
		}

		return startIndex;
	}

	std::vector<BatchRange> RenderDevice::computeBatches()
	{
		std::vector<BatchRange> batches;
		int begin = 0;
		int current = 0;
		int last = m_renderables.size();

		while (current < last)
		{
			while (current < last && m_renderables[begin]->isBatchEqualTo(m_renderables[current]))
				current++;

			batches.push_back(BatchRange(begin, current - 1));
			begin = current;

			if (current == last)
				break;
		}

		return batches;
	}

	int RenderDevice::findFirstIndexInBatch(Renderable* renderable)
	{
		for (unsigned int i = 0; i < m_renderables.size(); i++)
		{
			if (renderable->isBatchEqualTo(m_renderables[i]))
				return i;
		}

		return m_renderables.size();
	}
}

#endif

#ifdef NEW_STUFF

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
				if (list[i]->isBatchEqualTo(proto))
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
				= groupByBatches(m_renderables);

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

			// reserve memory
			unsigned int indexArrayCount = 0;
			for (unsigned int i = 0; i < m_renderables.size(); i++) {
				indexArrayCount += m_renderables[i]->getMesh()->getIndices()->size();
			}
			m_indices.reserve(indexArrayCount);

			unsigned int offset = 0;
			for (unsigned int i = 0; i < m_renderables.size(); i++)
			{
				std::vector<GLushort> newIndices = *m_renderables[i]->getMesh()->getIndices();
				for (unsigned int i = 0; i < newIndices.size(); i++)
					newIndices[i] += offset;

				m_indices.insert(m_indices.end(), newIndices.begin(), newIndices.end());

				offset += m_renderables[i]->getMesh()->getNumVertices();
			}

			m_isDirty = false;
		}
	}

	void RenderBatch::calculateVertices()
	{
		m_vertices.clear();

		// reserve memory
		unsigned int vertexArrayCount = 0;
		for (unsigned int i = 0; i < m_renderables.size(); i++) {
			vertexArrayCount += m_renderables[i]->getMesh()->getVertexData()->size();
		}
		m_vertices.reserve(vertexArrayCount);

		// compute camera matrices
		m_worldCamMatrix = Camera::getInstance()->calcCamMatrix(TransformSpace::World);
		m_localCamMatrix = Camera::getInstance()->calcCamMatrix(TransformSpace::Camera);

		// insert vertices
		for (unsigned int i = 0; i < m_renderables.size(); i++)
		{
			std::vector<float> vertices = computeTransformedVertices(m_renderables[i]);
			m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
		}
	}

	std::vector<float> RenderBatch::computeTransformedVertices(Renderable* renderable)
	{
		static Matrix3 worldCamMatrix = Matrix3();
		static Matrix3 localCamMatrix = Matrix3();

		// compute mvp matrix
		Transform* transform = renderable->getTransform();
		Matrix3 camMatrix = transform->transformSpace == TransformSpace::World
			? m_worldCamMatrix : m_localCamMatrix;
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

#endif