#pragma once

#include "../Libraries/GL.h"

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include <vector>

namespace Video
{
	class Mesh_v2
	{
	public:
		// get a static textured quad
		static Mesh_v2* GetTexturedQuad();

	public:
		// ctor
		Mesh_v2(std::vector<GLfloat> vertexData, unsigned int numVertices, std::vector<GLushort> indices)
			: m_vertexData(vertexData), m_numVertices(numVertices), m_indices(indices)
		{}

		// get vertexData
		const std::vector<GLfloat>* GetVertexData() const { return &m_vertexData; }

		// get num vertices
		unsigned int GetNumVertices() const { return m_numVertices; }

		// get indices
		const std::vector<GLushort>* GetIndices() const { return &m_indices; }

	private:
		// vertex data
		std::vector<GLfloat> m_vertexData;

		// number of vertices encoded by vertex data
		unsigned int m_numVertices;

		// indices
		std::vector<GLushort> m_indices;
	};
}