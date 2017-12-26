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
		// add a mesh to the renderer
		// TODO: remove after refactoring
		void AddMesh(Mesh* const mesh) {};

		// initialize the buffers
		// TODO: Remove after refactoring
		void InitializeBuffers() {};

		// render
		// TODO: remove after refactoring
		void Render_old(Transform* transform, Mesh* mesh, Material* material) {};

		// render
		void Render();

	protected:
		// update vertex array
		void UpdateVertices(std::vector<GLfloat>& vertices, const std::vector<Renderer*>& renderers);

		// reserver the vertex buffer to hold the renderer data
		void ReserveVertexArray(std::vector<GLfloat>& vertices, const std::vector<Renderer*>& renderers);
	};
}