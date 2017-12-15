#include "Mesh.h"

#include "VideoManager.h"

namespace Video
{
	// get a static textured quad
	Mesh* Mesh::GetTexturedQuad()
	{
		static Mesh texturedQuad(
			{ Vector2D(-0.5f, -0.5f), Vector2D(0.5f, -0.5f), Vector2D(-0.5f, 0.5f), Vector2D(0.5f, 0.5f) },
			{ Vector2D(0.0f, 0.0f), Vector2D(1.0f, 0.0f), Vector2D(0.0f, 1.0f), Vector2D(1.0f, 1.0f) },
			{ 0, 1, 2, 1, 3, 2 }
		);

		return &texturedQuad;
	}

	// get a static flat quad
	Mesh* Mesh::GetFlatQuad()
	{
		static Mesh flatQuad(
			{ Vector2D(-0.5f, -0.5f), Vector2D(0.5f, -0.5f), Vector2D(-0.5f, 0.5f), Vector2D(0.5f, 0.5f) },
			{},
			{ 0, 1, 2, 1, 3, 2 }
		);

		return &flatQuad;
	}

	void Mesh::Initialize()
	{
		if (!m_isInitialized)
		{
			VideoManager::GetInstance()->GetRenderDevice()->AddMesh(this);
			m_isInitialized = true;
		}
	}

	int Mesh::GetVertexBufferLength()
	{
		int numVertexComponents = GetVertices().size() * 2;
		int numTexComponents = GetTexCoords().size() * 2;
		int len = numVertexComponents + numTexComponents;
		return len;
	}

	int Mesh::GetIndexBufferLength()
	{
		return GetIndices().size();
	}

	void Mesh::FillVertexBuffer(float* const buffer)
	{
		Exception::Assert(GetTexCoords().size() == 0 || GetVertices().size() == GetTexCoords().size(),
			"A mesh must either contain no texture coordinates or the number of vertices and texture coordinates must match");

		unsigned int numTexCoords = GetTexCoords().size();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < GetVertices().size(); i++)
		{
			Vector2D vertex = GetVertices().at(i);
			buffer[offset] = vertex.GetX();
			buffer[offset + 1] = vertex.GetY();
			offset += 2;

			if (i < numTexCoords)
			{
				Vector2D texCoord = GetTexCoords().at(i);
				buffer[offset] = texCoord.GetX();
				buffer[offset + 1] = texCoord.GetY();
				offset += 2;
			}
		}
	}

	void Mesh::FillIndexBuffer(int * const buffer)
	{		
		for (unsigned int i = 0; i < GetIndices().size(); i++)
		{
			buffer[i] = GetIndices().at(i);
		}
		
	}

	int Mesh::GetVertexStride()
	{
		bool hasTexCoords = GetTexCoords().size() > 0;
		int numVertexComponents = 2;
		int numTexComponents = hasTexCoords ? 2 : 0;
		int stride = (numVertexComponents + numTexComponents);
		return stride;
	}
}