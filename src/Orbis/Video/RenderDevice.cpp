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
	// get the total vertex buffer length of a mesh list
	int GetTotalVertexBufferLength(std::vector<Mesh*> meshes)
	{
		int len = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			len += meshes.at(i)->GetVertexBufferLength();
		}
	
		return len;
	}

	// get the total index buffer length of a mesh list
	int GetTotalIndexBufferLength(std::vector<Mesh*> meshes)
	{
		int len = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			len += meshes.at(i)->GetIndexBufferLength();
		}

		return len;
	}

	// fills a preallocated buffer with a mesh list's vertex data
	void FillGlobalVertexBuffer(std::vector<Mesh*> meshes, float* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < meshes.size(); i++) 
		{
			meshes.at(i)->FillVertexBuffer(buffer + offset);
			offset += meshes.at(i)->GetVertexBufferLength();
		}
	}

	// fills a preallocated buffer with a mesh list's index data
	void FillGlobalIndexBuffer(std::vector<Mesh*> meshes, int* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes.at(i)->FillIndexBuffer(buffer + offset);
			offset += meshes.at(i)->GetIndexBufferLength();
		}
	}

	// get the index of a mesh within the mesh list
	int GetMeshIndex(std::vector<Mesh*> meshes, Mesh* const mesh)
	{
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			if (meshes.at(i) == mesh)
				return i;
		}

		throw new Exception("Mesh was not found");
	}

	// get the vertex buffer offset for a given mesh
	int GetMeshVertexOffset(std::vector<Mesh*> meshes, Mesh* const mesh)
	{
		int index = GetMeshIndex(meshes, mesh);
		int offset = 0;
		for (int i = 0; i < index; i++)
		{
			offset += meshes.at(i)->GetVertexBufferLength();
		}

		return offset;
	}

	// get the index buffer offset for a given mesh
	int GetMeshIndexOffset(std::vector<Mesh*> meshes, Mesh* const mesh)
	{
		int index = GetMeshIndex(meshes, mesh);
		int byteOffset = 0;
		for (int i = 0; i < index; i++)
		{
			byteOffset += meshes.at(i)->GetIndexBufferLength();
		}
		return byteOffset;
	}
}

namespace Video
{
	RenderDevice::RenderDevice() :
		m_vertexBufferHandle(0), m_indexBufferHandle(0), m_areBuffersInitialized(false)
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

	void RenderDevice::Render(Transform* transform, Mesh* mesh, Material* material)
	{
		// setup rendering
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// setup shader
		material->GetShader()->Use();
		glEnableVertexAttribArray(material->GetShader()->GetAttributeHandle("a_vPosition"));

		// setup texture
		if (material->GetTexture() != NULL)
		{
			glBindTexture(GL_TEXTURE_2D, material->GetTexture()->GetTextureHandle());
			glActiveTexture(GL_TEXTURE0);
			glEnableVertexAttribArray(material->GetShader()->GetAttributeHandle("a_vTexCoord"));
			material->GetShader()->SetUniform("u_sSampler", 0);
		}

		// setup color
		if (material->GetIsColorUsed())
			material->GetShader()->SetUniform("u_vColor", material->GetColor());

		// compute mvp matrix
		bool isWorldSpaceTransformation = transform->GetTransformSpace() == TransformSpace::WorldSpace;
		Matrix4 modelMatrix = Matrix4::From2DTransform(transform->GetModelMatrix());
		Matrix4 viewMatrix = Matrix4::From2DTransform(isWorldSpaceTransformation ? Camera::GetViewMatrix() : Matrix3());
		Matrix4 mvpMatrix = Camera::GetProjectionMatrix(isWorldSpaceTransformation) * viewMatrix * modelMatrix;
		material->GetShader()->SetUniform("u_mTransform", mvpMatrix.Transposed());

		// compute the mesh's buffer offset
		int meshVertexOffset = GetMeshVertexOffset(m_meshes, mesh);
		int meshVertexStride = mesh->GetVertexStride();
		int meshIndexOffset = GetMeshIndexOffset(m_meshes, mesh);

		// render
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
		glVertexAttribPointer(material->GetShader()->GetAttributeHandle("a_vPosition"), 2, GL_FLOAT, GL_FALSE, meshVertexStride * sizeof(GLfloat), (void*)(meshVertexOffset * sizeof(GLfloat)));
		if (material->GetTexture() != NULL)
		{
			glVertexAttribPointer(material->GetShader()->GetAttributeHandle("a_vTexCoord"), 2, GL_FLOAT, GL_FALSE, meshVertexStride * sizeof(GLfloat), (void*)(meshVertexOffset * sizeof(GLfloat) + 2 * sizeof(GLfloat)));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);
		glDrawElements(mesh->GetRenderMode(), 6, GL_UNSIGNED_INT, (void*)(meshIndexOffset * sizeof(GLint)));

		// cleanup
		glDisableVertexAttribArray(material->GetShader()->GetAttributeHandle("a_vPosition"));
		if (material->GetTexture() != NULL) {
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableVertexAttribArray(material->GetShader()->GetAttributeHandle("a_vTexCoord"));
		}
		glDisable(GL_BLEND);
		material->GetShader()->Unuse();
	}

	void RenderDevice::InitializeBuffers()
	{
		// generate the vertex buffer
		int vertexBufferSize = GetTotalVertexBufferLength(m_meshes);
		float* vertexBufferData = new float[vertexBufferSize];
		FillGlobalVertexBuffer(m_meshes, vertexBufferData);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize * sizeof(GLfloat), vertexBufferData, GL_STATIC_DRAW);
		delete[] vertexBufferData;

		// generate the index buffer
		int indexBufferSize = GetTotalIndexBufferLength(m_meshes);
		int* indexBufferData = new int[indexBufferSize];
		FillGlobalIndexBuffer(m_meshes, indexBufferData);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize * sizeof(GLint), indexBufferData, GL_STATIC_DRAW);
		delete[] indexBufferData;
	}
}