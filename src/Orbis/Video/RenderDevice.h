#pragma once

#include "RenderMode.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderable.h"

#include "../Game/Transform.h"
#include "../Game/Entity.h"
using namespace Game;
using namespace Components;

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Rect.h"
#include "../../Base/Math/Range.h"
using namespace Math;

#include <vector>

namespace Video
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
		void AddRenderable(Renderable* renderable);

		// update a renderable
		void UpdateRenderable(Renderable* renderable);

		// delete a renderable
		void DeleteRenderable(Renderable* renderable);

		// clear all renderables
		void clear();

		// render
		void render();

		// draw a debug line (slow!)
		void DrawDebugLine(Vector2D start, Vector2D end, Color color);

		// draw a debug rect (slow!)
		void DrawDebugRect(Rect rect, Color color);

	protected:
		// update vertex array
		void UpdateVertexArray();

		// update the vertex array for the renderer with the given index using the given mvp matrix
		void InsertIntoVertexArray(Renderable* const renderable, Matrix3& mvpMatrix);

		// reserver the vertex buffer to hold the renderer data
		void ReserveVertexArray();

		// insert renderers indices at position in index array
		void UpdateIndexArray();

		// update the index array for the renderer at the given renderer index. The given offset is applied to the indices and an updated offset is returned
		void InsertIntoIndexArray(unsigned int rendererIndex, unsigned short& offset);

		// reserve index array space
		void ReserveIndexArray();

		// compute the vao start index for a given batch
		unsigned int ComputeVaoStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches);

		// compute the ibo (index buffer) start index for a given batch
		unsigned int ComputeIboStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches);

		// compute the batches
		std::vector<BatchRange> ComputeBatches();

		// find index of first renderer in render batch
		int FindFirstIndexInBatch(Renderable* renderable);

		// draw a debug primitve
		void DrawDebugPrimitive(GLfloat* vertexArray, unsigned int vertexArraySize, Color color, RenderMode renderMode);

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