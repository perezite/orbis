#include "RenderDevice.h"

#include "VideoManager.h"
#include "Shader.h"
#include "Texture.h"
using namespace Video;

#include "../Core/LogHelper.h"
#include "../Libraries/SDL.h"
#include "../Libraries/GL.h"
#include "../Components/Camera.h"
using namespace Core;
using namespace Components;

#include "../../Base/System/Exception.h"
#include "../../Base/Math/Matrix4.h"
using namespace System;
using namespace Math;

namespace 
{
	// get size in bytes required to hold the vertex data of a mesh
	int GetVertexBufferSize(Mesh* const mesh)
	{
		int numVertexComponents = mesh->GetVertices().size() * 2;
		int numTexComponents = mesh->GetTexCoords().size() * 2;
		int size = numVertexComponents * sizeof(float) + numTexComponents * sizeof(float);
		return size;
	}

	// fills a preallocated buffer with a mesh's vertex data
	void GetVertexData(Mesh* const mesh, float* const buffer) 
	{	
		Exception::Assert(mesh->GetTexCoords().size() == 0 || mesh->GetVertices().size() == mesh->GetTexCoords().size(),
			"A mesh must either contain no texture coordinates or the number of vertices and texture coordinates must match");

		unsigned int numTexCoords = mesh->GetTexCoords().size();
		unsigned int offset = 0;
		for (unsigned int i = 0; i < mesh->GetVertices().size(); i++)
		{
			Vector2D vertex = mesh->GetVertices().at(i);
			buffer[offset] = vertex.GetX();
			buffer[offset + 1] = vertex.GetY();
			offset += 2;

			if (i < numTexCoords)
			{
				Vector2D texCoord = mesh->GetTexCoords().at(i);
				buffer[offset + 2] = texCoord.GetX();
				buffer[offset + 3] = texCoord.GetY();
				offset += 2;
			}
		}
	}

	// get the size in bytes required to hold the index data of a mesh
	int GetIndexBufferSize(Mesh* const mesh)
	{
		return mesh->GetIndices().size() * sizeof(int);
	}

	// fills a preallocated buffer with a mesh's index data
	void GetIndexData(Mesh* const mesh, int* const buffer)
	{
		for (unsigned int i = 0; i < mesh->GetIndices().size(); i++)
		{
			buffer[i] = mesh->GetIndices().at(i);
		}
	}

	// get the total vertex buffer size of a mesh list in bytes
	int GetVertexBufferSize(std::vector<Mesh*> meshes)
	{
		int size = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			size += GetVertexBufferSize(meshes.at(i));
		}
	
		return size;
	}

	// get the total index buffer size of a mesh list in bytes
	int GetIndexBufferSize(std::vector<Mesh*> meshes)
	{
		int size = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			size += GetIndexBufferSize(meshes.at(i));
		}

		return size;
	}

	// fills a preallocated buffer with a mesh list's vertex data
	void GetVertexData(std::vector<Mesh*> meshes, float* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < meshes.size(); i++) 
		{
			GetVertexData(meshes.at(i), buffer + offset);
			offset += GetVertexBufferSize(meshes.at(i));
		}
	}

	// fills a preallocated buffer with a mesh list's index data
	void GetIndexData(std::vector<Mesh*> meshes, int* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			GetIndexData(meshes.at(i), buffer + offset);
			offset += GetIndexBufferSize(meshes.at(i));
		}
	}

	// get the index of a mesh within the mesh list
	int GetMeshIndex(std::vector<Mesh*> meshes, Mesh* const mesh)
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			auto temp = meshes.at(i);
			if (meshes.at(i) == mesh)
				return i;
		}

		throw new Exception("Mesh was not found");
	}

	// get the buffer offset for a given mesh within a list of meshes in bytes
	int GetMeshOffset(std::vector<Mesh*> meshes, Mesh* const mesh)
	{
		int index = GetMeshIndex(meshes, mesh);
		int byteOffset = 0;
		for (int i = 0; i < index; i++)
		{
			byteOffset += GetVertexBufferSize(meshes.at(i));
			byteOffset += GetIndexBufferSize(meshes.at(i));
		}

		return byteOffset;
	}

	// get the mesh meshStride in bytes
	int GetMeshStride(Mesh* const mesh)
	{
		bool hasTexCoords = mesh->GetTexCoords().size() > 0;
		int numVertexComponents = 2;
		int numTexComponents = hasTexCoords ? 2 : 0;
		int stride = (numVertexComponents + numTexComponents) * sizeof(GLfloat);
		return stride;
	}
}

namespace Video
{
	RenderDevice::RenderDevice() :
		m_areBuffersInitialized(false), m_vertexBufferHandle(0), m_indexBufferHandle(0)
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);

		glGenBuffers(1, &m_vertexBufferHandle);
		glGenBuffers(1, &m_indexBufferHandle);
	}

	RenderDevice::~RenderDevice()
	{
		glDeleteBuffers(1, &m_vertexBufferHandle);
		glDeleteBuffers(1, &m_indexBufferHandle);
	}

	void RenderDevice::AddMesh(Mesh* const mesh)
	{
		Exception::Assert(m_areBuffersInitialized == false, "Adding meshes to the render device is not allowed after the first rendering cycle");
		m_meshes.push_back(mesh);
	}

	void RenderDevice::Render(Mesh* mesh, Transform* transform, Texture* texture, Shader* shader, const Color& color, RenderMode renderMode, bool useColor, bool applyCameraTransformation)
	{
		// setup rendering
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// setup shader
		shader->Use();
		glEnableVertexAttribArray(shader->GetAttributeHandle("a_vPosition"));

		// setup texture
		if (texture != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, texture->GetTextureHandle());
			glActiveTexture(GL_TEXTURE0);
			glEnableVertexAttribArray(shader->GetAttributeHandle("a_vTexCoord"));
			shader->SetUniform("u_sSampler", 0);
		}

		// setup color
		if (useColor)
			shader->SetUniform("u_vColor", color);

		// compute mvp matrix
		Matrix4 modelMatrix = Matrix4::From2DTransform(transform->GetMatrix());
		Matrix4 viewMatrix = Matrix4::From2DTransform(applyCameraTransformation ? Camera::GetViewMatrix() : Matrix3());
		Matrix4 mvpMatrix = Camera::GetProjectionMatrix(applyCameraTransformation) * viewMatrix * modelMatrix;
		shader->SetUniform("u_mTransform", mvpMatrix.Transposed());

		// compute the mesh's buffer offset
		// TODO: Precompute and buffer this
		int meshOffset = GetMeshOffset(m_meshes, mesh);
		int meshStride = GetMeshStride(mesh);

		// render
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
		// glVertexAttribPointer(shader->GetAttributeHandle("a_vPosition"), 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(GLfloat), NULL);
		glVertexAttribPointer(shader->GetAttributeHandle("a_vPosition"), 2, GL_FLOAT, GL_FALSE, meshStride, (void*)meshOffset);
		if (texture != NULL)
		{
			// glVertexAttribPointer(shader->GetAttributeHandle("a_vTexCoord"), 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(GLfloat), (void*)(0 + 2 * sizeof(GL_FLOAT)));
			glVertexAttribPointer(shader->GetAttributeHandle("a_vTexCoord"), 2, GL_FLOAT, GL_FALSE, meshStride, (void*)(meshOffset + 2 * sizeof(GL_FLOAT)));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);
		glDrawElements(renderMode, 6, GL_UNSIGNED_INT, NULL);

		// cleanup
		glDisableVertexAttribArray(shader->GetAttributeHandle("a_vPosition"));
		if (texture != NULL) {
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableVertexAttribArray(shader->GetAttributeHandle("a_vTexCoord"));
		}
		glDisable(GL_BLEND);
		shader->Unuse();
	}

	void RenderDevice::InitializedBuffers()
	{
		// generate the vertex buffer
		int vertexBufferSize = GetVertexBufferSize(m_meshes);
		float* vertexBufferData = new float[vertexBufferSize];
		GetVertexData(m_meshes, vertexBufferData);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, vertexBufferData, GL_STATIC_DRAW);
		delete[] vertexBufferData;

		// generate the index buffer
		int indexBufferSize = GetIndexBufferSize(m_meshes);
		int* indexBufferData = new int[indexBufferSize];
		GetIndexData(m_meshes, indexBufferData);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBufferData, GL_STATIC_DRAW);
		delete[] indexBufferData;
	}
}