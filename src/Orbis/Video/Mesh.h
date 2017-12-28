#pragma once

#include "Color.h"
#include "RenderMode.h"

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include <set>
#include <vector>

namespace Video
{
	// a mesh represents the appearance of an entity on the screen
	class Mesh 
	{
	public:
		// get a static textured quad
		static Mesh* GetTexturedQuad();

		// get a static flat quad
		static Mesh* GetFlatQuad();

		// get a static line mesh
		static Mesh* GetLineMesh() { return NULL; }

	public:
		// ctor
		Mesh(std::vector<GLfloat> vertexData, unsigned int vertexSize, std::vector<GLuint> indices)
			: m_vertexData(vertexData), m_vertexSize(vertexSize), m_indices(indices)
		{}

		// get vertexData
		const std::vector<GLfloat>* GetVertexData() const { return &m_vertexData; }

		// get num vertices
		unsigned int GetNumVertices() const { return m_vertexData.size() / m_vertexSize; }

		// get vertex size
		unsigned int GetVertexSize() const { return m_vertexSize; }

		// get indices
		const std::vector<GLuint>* GetIndices() const { return &m_indices; }

	private:
		// vertex data
		std::vector<GLfloat> m_vertexData;

		// size (number of elements) per vertex
		unsigned int m_vertexSize;

		// indices
		std::vector<GLuint> m_indices;
	};
}