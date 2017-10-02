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
		m_colors.clear();
		m_indices.clear();
	}

	void Renderer::EndPrimitive(float rotation)
	{
		m_shader.SetIndices(m_indices);
		m_shader.SetVertices(m_vertices, m_colors);
		m_shader.Render(m_vertices, m_colors, rotation, m_renderMode);
	}

	void Renderer::SetVertex2D(Vector2D position)
	{
		m_vertices.push_back(position);
		m_colors.push_back(Color(0.0f, 0.0f, 1.0f, 1.0f));

		unsigned int lastIndex = m_indices.empty() ? -1 : m_indices.back();
		m_indices.push_back(lastIndex + 1);

	}
}