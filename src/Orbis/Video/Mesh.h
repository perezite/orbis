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
		// TODO: Remove after refactoring
		Mesh(std::vector<Vector2D> vertices, std::vector<Vector2D> texCoords, std::vector<int> indices, RenderMode renderMode = RenderMode::Triangles)
		{}

		// ctor
		Mesh(std::vector<GLfloat> vertexData, unsigned int vertexSize, std::vector<GLushort> indices)
			: m_vertexData(vertexData), m_vertexSize(vertexSize), m_indices(indices)
		{}


		// get vertices
		// TODO: Remove after refactoring
		std::vector<Vector2D> GetVertices() const { return std::vector<Vector2D>(); }

		// get tex corodinates
		// TODO: Remove after refactoring
		std::vector<Vector2D> GetTexCoords() const { return std::vector<Vector2D>(); }

		// get indices
		// TODO: Remove after refactoring
		std::vector<int> GetIndices_old() const { return std::vector<int>(); }

		// get render mode
		// TODO: remove after refactoring
		RenderMode GetRenderMode() const { return RenderMode::Triangles; }

		// get vertex buffer length required to store the mesh's vertex data
		// TODO: remove after refactoring
		int GetVertexBufferLength() { return 42; }

		// get index buffer length required to store the mesh's vertex data
		// TODO: remove after refactoring
		int GetIndexBufferLength() { return 42; }
		
		// fills a preallocated buffer with the mesh's vertex data
		// TODO: remove after refactoring
		void FillVertexBuffer(float* const buffer) { }

		// fills a preallocated buffer with the mesh's index data
		// TODO: remove after refactoring
		void FillIndexBuffer(int* const buffer) { }

		// get the mesh's vertex stride
		// TODO: remove after refactoring
		int GetVertexStride() { return 42; };

		// initialize the mesh. Must be called before rendering
		// TODO: remove after refactoring
		void Initialize() { };

		// get vertexData
		const std::vector<GLfloat>* GetVertexData() const { return &m_vertexData; }

		// get num vertices
		unsigned int GetNumVertices() const { return m_vertexData.size() / m_vertexSize; }

		// get vertex size
		unsigned int GetVertexSize() const { return m_vertexSize; }

		// get indices
		const std::vector<GLushort>* GetIndices() const { return &m_indices; }

	private:
		// vertex data
		std::vector<GLfloat> m_vertexData;

		// size (number of elements) per vertex
		unsigned int m_vertexSize;

		// indices
		std::vector<GLushort> m_indices;
	};
}