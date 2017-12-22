#pragma once

#include "Mesh.h"
#include "RenderBatch.h"

#include <vector>

namespace Video
{
	class RenderBatchHelper
	{
	public: 
		// get the total vertex buffer length of a mesh list
		static int GetVertexBufferLength(std::vector<RenderBatch> batches);

		// get the total index buffer length of a mesh list
		static int GetIndexBufferLength(std::vector<RenderBatch> batches);

		// fills a preallocated buffer with a render batches vertex data
		static void FillVertexBufferData(std::vector<RenderBatch> batches, float* const buffer);

		// fills a preallocated buffer with a render batches index data
		static void FillIndexBufferData(std::vector<RenderBatch> batches, int* const buffer);

		// get the index of a mesh within the mesh list
		static int GetIndex(std::vector<RenderBatch>* batches, RenderBatch* const batch);

		// get the vertex buffer offset for a given render batch
		static int GetVertexBufferOffset(std::vector<RenderBatch>* batches, RenderBatch* const batch);

		// get the index buffer offset for a given render batch
		static int GetIndexBufferOffset(std::vector<RenderBatch>* batches, RenderBatch* const batch);

		// find a matching render batch or NULL for the given render item
		static RenderBatch* FindMatchingRenderBatch(Mesh * mesh, Material * material, std::vector<RenderBatch>* batches);
	};
}