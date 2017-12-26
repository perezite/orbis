#pragma once

#include "RenderMode.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"

#include "../Game/Transform.h"
#include "../Game/Entity_v2.h"
using namespace Game;

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
		void Render(const std::vector<Entity_v2>& entities);

	protected:
		// update vertex array
		void UpdateVertices(std::vector<GLfloat>& vertices, const std::vector<Entity_v2>& entities);
	};
}