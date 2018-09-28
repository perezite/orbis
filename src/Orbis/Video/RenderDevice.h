#pragma once

#include "RenderMode.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderable.h"

#include "../Game/Transform.h"
#include "../Game/Entity.h"

#include "../../Base/Base.h"
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
			: m_areIndexesDirty(false)
		{}

		// add a renderable
		void addRenderable(Renderable* renderable);

		// updateLevel a renderable
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

		// reserve the vertex buffer to hold the renderer data
		void reserveVertexArray();

		// insert renderers indexes at position in index data
		void updateIndexArray();

		// update the index array for the renderer at the given renderer index. The given offset is applied to the indices and an updated offset is returned
		void insertIntoIndexArray(unsigned int rendererIndex, unsigned short& offset);

		// reserve index array space
		void reserveIndexArray();

		// update the batches
		void updateBatches();

		// compute the vao start index for a given batch
		unsigned int computeVaoStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches);

		// compute the ibo (index buffer) start index for a given batch
		unsigned int computeIboStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches);

		// find index of first renderer in render batch
		int findFirstIndexInBatch(Renderable* renderable);

	private:
		// the vertexes 
		std::vector<GLfloat> m_vertexes;

		// the indexes
		std::vector<GLushort> m_indexes;

		// the batches
		std::vector<BatchRange> m_batches;

		// are the indexes in dirty state
		bool m_areIndexesDirty;

		// the renderables
		std::vector<Renderable*> m_renderables;
	};
}