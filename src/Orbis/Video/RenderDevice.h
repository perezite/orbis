#pragma once

#include "RenderMode.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"

#include "../Game/Transform.h"
#include "../Game/Entity.h"
#include "../Components/Renderer.h"
using namespace Game;
using namespace Components;

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Rect.h"
using namespace Math;

#include <vector>

namespace Video
{
	class RenderDevice
	{
	public:
		// ctor
		RenderDevice()
			: m_isIndexArrayDirty(false)
		{}

		// add a renderer
		void AddRenderer(Renderer* renderer);

		// update a renderer
		void UpdateRenderer(Renderer* renderer);

		// render
		void Render();

		// draw a debug line (slow!)
		void DrawDebugLine(Vector2D start, Vector2D end, Color color);

		// draw a debug rect (slow!)
		void DrawDebugRect(Rect rect, Color color);

	protected:
		// update vertex array
		void UpdateVertexArray();

		// reserver the vertex buffer to hold the renderer data
		void ReserveVertexArray();

		// insert renderers indices at position in index array
		void UpdateIndexArray();

		// reserve index array space
		void ReserveIndexArray();

		// find index of first renderer in render batch
		int FindFirstIndexInBatch(Renderer* renderer);

		// draw a debug primitve
		void DrawDebugPrimitive(GLfloat* vertexArray, unsigned int vertexArraySize, Color color, RenderMode renderMode);

	private:
		// the vertex array
		std::vector<GLfloat> m_vertexArray;

		// the index array
		std::vector<GLuint> m_indexArray;

		// is the index array in dirty state
		bool m_isIndexArrayDirty;

		// the renderer components
		std::vector<Renderer*> m_renderers;
	};
}