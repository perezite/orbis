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

		// add a mesh to the renderer
		// TODO: remove after refactoring
		void AddMesh(Mesh* const mesh) {};

		// initialize the buffers
		// TODO: Remove after refactoring
		void InitializeBuffers() {};

		// add a renderer
		void AddRenderer(Renderer* renderer);

		// update a renderer
		void UpdateRenderer(Renderer* renderer);

		// render
		// TODO: remove after refactoring
		void Render_old(Transform* transform, Mesh* mesh, Material* material) {};

		// render
		void Render();

		// draw a debug line
		void DrawDebugLine(Vector2D start, Vector2D end, Color color);

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