#pragma once

#include "Component.h"

#include "../Video/Shader.h"
#include "../Video/Color.h"
using namespace Video;

namespace Components
{
	// Renders a colored quad
	class RectangleRenderer : public Component
	{
	public:
		// ctor
		RectangleRenderer(Color const &color) { m_color = color; }

		// dtor
		virtual ~RectangleRenderer() { delete m_shader; }

		// update
		void Start();

		// render
		void Render();

	private:
		// the color
		Color m_color;

		// the shader
		Shader* m_shader;
	};
}