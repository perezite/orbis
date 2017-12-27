#pragma once

#include "../Libraries/GL.h"

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include <vector>

namespace Video
{
	// a collection of data describing the untransformed physical appearance of an entity
	class Mesh_v2
	{
	public:
		// get a static textured quad
		static Mesh_v2* GetTexturedQuad();

		// get a static flat (un-textured) quad
		static Mesh_v2* GetFlatQuad();

	public:
		// ctor
		Mesh_v2(std::vector<GLfloat> vertexData, unsigned int vertexSize, std::vector<GLushort> indices)
			: m_vertexData(vertexData), m_vertexSize(vertexSize), m_indices(indices)
		{}

		// get vertexData
		const std::vector<GLfloat>* GetVertexData() const { return &m_vertexData; }

		// get num vertices
		unsigned int GetNumVertices() const { return m_vertexData.size() / m_vertexSize; }

		// get vertex size
		unsigned int GetVertexSize() const { return m_vertexSize; }

		// get indices
		const std::vector<GLushort>* GetIndices() const { return &m_indices; }

		// get vertex buffer stride
		int GetVertexStride();

	private:
		// vertex data
		std::vector<GLfloat> m_vertexData;

		// number of vertices in the mesh
		unsigned int m_numVertices;

		// size (number of elements) per vertex
		unsigned int m_vertexSize;

		// indices
		std::vector<GLushort> m_indices;
	};
}