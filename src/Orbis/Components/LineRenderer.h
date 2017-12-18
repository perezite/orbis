#pragma once

#include "Component.h"

#include "../Video/Shader.h"
#include "../Video/Mesh.h"
using namespace Video;

namespace Components
{
	class LineRenderer : public Component
	{
	public:
		// add line
		void AddLine(Vector2D begin, Vector2D end) { m_lines.push_back(std::make_pair(begin, end)); }

		// clear all lines 
		void ClearLines() { m_lines.clear(); };

		// start
		void Start();

		// render
		void Render();

	private: 
		// the shader
		Shader* m_shader;

		// the mesh
		Mesh* m_mesh;

		// the lines
		std::vector<std::pair<Vector2D, Vector2D>> m_lines;
	};
}