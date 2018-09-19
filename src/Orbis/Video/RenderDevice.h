#pragma once

#include "RenderMode.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderable.h"

#include "../Game/Transform.h"
#include "../Game/Entity.h"

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Rect.h"
#include "../../Base/Math/Range.h"
using namespace base;

#include <vector>

namespace orb
{
	typedef Range<unsigned int> BatchRange;

	class RenderDevice
	{
	public:
		// ctor
		RenderDevice()
			: m_isIndexArrayDirty(false)
		{}

		// add a renderable
		void addRenderable(Renderable* renderable);

		// update a renderable
		void updateRenderable(Renderable* renderable);

		// delete a renderable
		void deleteRenderable(Renderable* renderable);

		// clear all renderables
		void clear();

		// render
		void render();

	protected:
		// update vertex array
		void updateVertexArray();

		// update the vertex array for the renderer with the given index using the given mvp matrix
		void insertIntoVertexArray(Renderable* const renderable, Matrix3& mvpMatrix);

		// reserver the vertex buffer to hold the renderer data
		void reserveVertexArray();

		// insert renderers indices at position in index array
		void updateIndexArray();

		// update the index array for the renderer at the given renderer index. The given offset is applied to the indices and an updated offset is returned
		void insertIntoIndexArray(unsigned int rendererIndex, unsigned short& offset);

		// reserve index array space
		void reserveIndexArray();

		// compute the vao start index for a given batch
		unsigned int computeVaoStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches);

		// compute the ibo (index buffer) start index for a given batch
		unsigned int computeIboStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches);

		// compute the batches
		std::vector<BatchRange> computeBatches();

		// find index of first renderer in render batch
		int findFirstIndexInBatch(Renderable* renderable);

	private:
		// the vertex array
		std::vector<GLfloat> m_vertexArray;

		// the index array
		std::vector<GLushort> m_indexArray;

		// is the index array in dirty state
		bool m_isIndexArrayDirty;

		// the renderables
		std::vector<Renderable*> m_renderables;
	};
}