#pragma once

#include "RenderMode.h"
#include "Shader_v2.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"

#include "../Game/Transform.h"
using namespace Game;

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include "../Game/Entity_v2.h"
using namespace Game;

#include <vector>

namespace Video
{
	class RenderDevice_v2
	{
	public:
		// render
		void Render(const std::vector<Entity_v2>& entities);

	protected:
		// update vertex array
		void UpdateVertices(std::vector<GLfloat>& vertices, const std::vector<Entity_v2>& entities);
	};
}