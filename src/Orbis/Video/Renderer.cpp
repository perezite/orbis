#include "Renderer.h"

#include "../../Base/System/Exception.h"
using namespace System;

namespace Video
{
	Renderer::~Renderer()
	{
	}

	void Renderer::BeginPrimitive(RenderMode renderMode)
	{
		m_renderMode = renderMode;
		m_vertices.clear();
	}

	void Renderer::EndPrimitive()
	{
		// setup shader
		static const float color[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		std::vector<Color> colors;
		for (unsigned int i = 0; i < m_vertices.size(); i++)
			colors.push_back(Color(color[0], color[1], color[2], color[3]));
		m_shader.Render(m_vertices, colors, m_renderMode);
	}

	void Renderer::SetVertex2D(Vector2D position)
	{
		m_vertices.push_back(position);
	}
}