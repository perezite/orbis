#pragma once

#include "Color.h"
#include "RenderMode.h"

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
		Mesh(std::vector<GLfloat> vertexData, unsigned int vertexCount, std::vector<GLushort> indexes, bool isVertexColored = false)
			: m_vertexes(vertexData), m_vertexCount(vertexCount), m_indexes(indexes), m_isVertexColored(isVertexColored)
		{}

		// get vertexData (deprecated)
		const std::vector<GLfloat>* getVertexes2() const { return &m_vertexes; }

		std::vector<GLfloat> getVertexes() { return m_vertexes; }

		// get num vertexes
		unsigned int getNumVertexes() const { return m_vertexes.size() / m_vertexCount; }

		// get the count of one vertex
		unsigned int getVertexCount() const { return m_vertexCount; }

		// get indexes (deprecated)
		const std::vector<GLushort>* getIndexes2() const { return &m_indexes; }

		// get indexes
		std::vector<GLushort> getIndexes() { return m_indexes; }

		// is vertex colored
		bool isVertexColored() const { return m_isVertexColored; }

	private:
		// vertex data
		std::vector<GLfloat> m_vertexes;

		// number of elements per vertex
		unsigned int m_vertexCount;

		// indexes
		std::vector<GLushort> m_indexes;

		// is the mesh vertex color
		bool m_isVertexColored;
	};
}