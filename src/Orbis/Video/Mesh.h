#pragma once

#include "Color.h"

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include <vector>

namespace Video
{
	// a mesh represents the appearance of an entity on the screen
	class Mesh 
	{
	public:
		// a textured quad
		static Mesh TexturedQuad;

		// a flat quad without texture
		static Mesh FlatQuad;

	public:
		// ctor
		Mesh(std::vector<Vector2D> vertices, std::vector<Vector2D> texCoords, std::vector<int> indices) 
			: m_vertices(vertices),  m_texCoords(texCoords), m_indices(indices), m_isInitialized(false)
			{}

		// get vertices
		std::vector<Vector2D> GetVertices() const { return m_vertices; }

		// get tex corodinates
		std::vector<Vector2D> GetTexCoords() const { return m_texCoords; }

		// get indices
		std::vector<int> GetIndices() const { return m_indices; }

		// initialize the mesh. Must be called before rendering
		void Initialize();

	private:
		// the vertex coordinates
		std::vector<Vector2D> m_vertices;

		// the texture coordinates
		std::vector<Vector2D> m_texCoords;

		// the vertex indices
		std::vector<int> m_indices;

		// is the mesh initialized
		bool m_isInitialized;
	};
}