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
		// create a vertex color textured quad
		static Mesh* CreateVertexColoredTexturedQuad(Color color);

		// create a textured quad
		static Mesh* CreateTexturedQuad();

		// create a flat quad
		static Mesh* CreateFlatQuad();

	public:
		// ctor
		Mesh(std::vector<GLfloat> vertexData, unsigned int vertexSize, std::vector<GLushort> indices, bool isVertexColored = false)
			: m_vertexData(vertexData), m_vertexSize(vertexSize), m_indices(indices), m_isVertexColored(isVertexColored)
		{}

		// get vertexData
		const std::vector<GLfloat>* GetVertexData() const { return &m_vertexData; }

		// get num vertices
		unsigned int GetNumVertices() const { return m_vertexData.size() / m_vertexSize; }

		// get the size of one vertex
		unsigned int GetVertexSize() const { return m_vertexSize; }

		// get indices
		const std::vector<GLushort>* GetIndices() const { return &m_indices; }

		// is vertex colored
		bool IsVertexColored() const { return m_isVertexColored; }

	private:
		// vertex data
		std::vector<GLfloat> m_vertexData;

		// size (number of elements) per vertex
		unsigned int m_vertexSize;

		// indices
		std::vector<GLushort> m_indices;

		// is the mesh vertex color
		bool m_isVertexColored;
	};
}