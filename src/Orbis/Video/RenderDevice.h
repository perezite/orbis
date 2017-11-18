#pragma once

#include "RenderMode.h"
#include "Shader.h"
#include "Texture.h"

#include "../Game/Transform.h"
using namespace Game;

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include <vector>

namespace Video
{
	class RenderDevice
	{
	public:
		// ctor
		RenderDevice();

		// dtor
		virtual ~RenderDevice();

		// add geometry to the renderer
		void AddGeometry(std::vector<Vector2D> vertices, std::vector<Vector2D> texCoordinates, std::vector<int> indices);

		// render
		void Render(Transform* transform, Texture* texture);

	private:
		// the vertices of the primitive
		std::vector<Vector2D> vertices;
	};
}