#pragma once

#include "Color.h"
#include "RenderMode.h"

#include "../Game/Transform.h"
#include "Texture.h"

#include "../../Base/Base.h"
using namespace base;

#include <set>
#include <vector>

namespace orb
{
	// a mesh represents the appearance of an entity on the screen
	class Mesh
	{
	public:
		// create a vertex color textured quad
		static Mesh* createVertexColoredTexturedQuad(Color color);

		// create a textured quad
		static Mesh* createTexturedQuad();

		// create a flat quad
		static Mesh* createFlatQuad();

	public:
		// ctor
		Mesh(std::vector<GLfloat> vertexData, unsigned int vertexCount, std::vector<GLushort> indices, bool isVertexColored = false)
			: m_vertexData(vertexData), m_vertexCount(vertexCount), m_indices(indices), m_isVertexColored(isVertexColored)
		{}

		// get vertexData
		const std::vector<GLfloat>* getVertexData() const { return &m_vertexData; }

		// get num vertices
		unsigned int getNumVertices() const { return m_vertexData.size() / m_vertexCount; }

		// get the size of one vertex
		unsigned int getVertexCount() const { return m_vertexCount; }

		// get count of indices
		unsigned int getIndexCount() const { return m_indices.size(); }

		// compute indices
		const void computeIndices(std::vector<GLushort>& result, unsigned int offset = 0) const;

		// get indices
		const std::vector<GLushort>* getIndices() const { return &m_indices; }

		// is vertex colored
		bool isVertexColored() const { return m_isVertexColored; }

		// compute transformed vertices
		void computeTransformedVertices(std::vector<float>& result, Transform* transform, Texture* tex);

	private:
		// vertex data
		std::vector<GLfloat> m_vertexData;

		// count per vertex
		unsigned int m_vertexCount;

		// indices
		std::vector<GLushort> m_indices;

		// is the mesh vertex color
		bool m_isVertexColored;
	};
}