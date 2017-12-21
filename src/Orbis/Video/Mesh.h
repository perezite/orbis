#pragma once

#include "Color.h"
#include "RenderMode.h"

#include "../Game/Transform.h"
using namespace Game;

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
		static Mesh* GetLineMesh();

	public:
		// ctor
		Mesh(std::vector<Vector2D> vertices, std::vector<Vector2D> texCoords, std::vector<int> indices, RenderMode renderMode = RenderMode::Triangles);

		// get vertices
		std::vector<Vector2D> GetVertices() const { return m_vertices; }

		// get vertex pointer
		Vector2D* GetVertex(int index) { return &m_vertices.at(index); }

		// get tex corodinates
		std::vector<Vector2D> GetTexCoords() const { return m_texCoords; }

		// get indices
		std::vector<int> GetIndices() const { return m_indices; }

		// get render mode
		RenderMode GetRenderMode() const { return m_renderMode; }

		// get vertex buffer length required to store the mesh's vertex data
		int GetVertexBufferLength();

		// get index buffer length required to store the mesh's vertex data
		int GetIndexBufferLength();

		// fills a preallocated buffer with the mesh's vertex data
		void FillVertexBuffer(float* const buffer);

		// fills a preallocated buffer with the mesh's index data
		void FillIndexBuffer(int* const buffer);

		// get the mesh's vertex stride
		int GetVertexStride();

		// apply the given transformation on the mesh
		Mesh Transformed(const Transform* transform);

		// get number of elements per primitive
		int GetNumElements();

	private:
		// the vertex coordinates
		std::vector<Vector2D> m_vertices;

		// the texture coordinates
		std::vector<Vector2D> m_texCoords;

		// the vertex indices
		std::vector<int> m_indices;

		// the render mode
		RenderMode m_renderMode;
	};
}