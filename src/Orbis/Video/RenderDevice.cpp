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
	int GetTotalVertexBufferLength(std::vector<Mesh> meshes)
	{
		int len = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			len += meshes.at(i).GetVertexBufferLength();
		}
	
		return len;
	}

	// get the total index buffer length of a mesh list
	int GetTotalIndexBufferLength(std::vector<Mesh> meshes)
	{
		int len = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			len += meshes.at(i).GetIndexBufferLength();
		}

		return len;
	}

	// fills a preallocated buffer with a mesh list's vertex data
	void FillGlobalVertexBuffer(std::vector<Mesh> meshes, float* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < meshes.size(); i++) 
		{
			meshes.at(i).FillVertexBuffer(buffer + offset);
			offset += meshes.at(i).GetVertexBufferLength();
		}
	}

	// fills a preallocated buffer with a mesh list's index data
	void FillGlobalIndexBuffer(std::vector<Mesh> meshes, int* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes.at(i).FillIndexBuffer(buffer + offset);
			offset += meshes.at(i).GetIndexBufferLength();
		}
	}

	// get the index of a mesh within the mesh list
	int GetMeshIndex(std::vector<Mesh>* meshes, Mesh* const mesh)
	{
		for (unsigned int i = 0; i < meshes->size(); i++)
		{
			if (&meshes->at(i) == mesh)
				return i;
		}

		throw new Exception("Mesh was not found");
	}

	// get the vertex buffer offset for a given mesh
	int GetMeshVertexOffset(std::vector<Mesh>* meshes, Mesh* const mesh)
	{
		int index = GetMeshIndex(meshes, mesh);
		int offset = 0;
		for (int i = 0; i < index; i++)
		{
			offset += meshes->at(i).GetVertexBufferLength();
		}

		return offset;
	}

	// get the index buffer offset for a given mesh
	int GetMeshIndexOffset(std::vector<Mesh>* meshes, Mesh* const mesh)
	{
		int index = GetMeshIndex(meshes, mesh);
		int byteOffset = 0;
		for (int i = 0; i < index; i++)
		{
			byteOffset += meshes->at(i).GetIndexBufferLength();
		}
		return byteOffset;
	}
}

namespace Video
{
	RenderDevice::RenderDevice() :
		m_vertexBufferHandle(0), m_indexBufferHandle(0)
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

	void RenderDevice::Begin()
	{
		m_renderData.clear();
	}

	void RenderDevice::Finalize()
	{
		// compute transformed meshes
		std::vector<Mesh> transformedMeshes;
		for (unsigned int i = 0; i < m_renderData.size(); i++)
		{
			std::tuple<Transform, Mesh*, Material*> data = m_renderData.at(i);
			Transform* transform = &std::get<0>(data);
			Mesh mesh = std::get<1>(data)->Transformed(transform);
			transformedMeshes.push_back(mesh);
		}

		// update vbo and ibo
		UpdateBuffers(transformedMeshes);

		// perform rendering
		for (unsigned int i = 0; i < m_renderData.size(); i++)
		{
			std::tuple<Transform, Mesh*, Material*> data = m_renderData.at(i);
			RenderSingle(&std::get<0>(data), &transformedMeshes.at(i), std::get<2>(data), &transformedMeshes);
		}
	}

	void RenderDevice::Render(Transform* transform, Mesh* mesh, Material* material)
	{
		m_renderData.push_back(std::make_tuple(*transform, mesh, material));
	}

	void RenderDevice::RenderSingle(Transform* transform, Mesh* mesh, Material* material, std::vector<Mesh>* meshList)
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

		// compute the mesh's buffer offset
		int meshVertexOffset = GetMeshVertexOffset(meshList, mesh);
		int meshVertexStride = mesh->GetVertexStride();
		int meshIndexOffset = GetMeshIndexOffset(meshList, mesh);

		// prepare render
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
		glVertexAttribPointer(material->GetShader()->GetAttributeHandle("a_vPosition"), 2, GL_FLOAT, GL_FALSE, meshVertexStride * sizeof(GLfloat), (void*)(meshVertexOffset * sizeof(GLfloat)));
		if (material->GetTexture() != NULL)
		{
			glVertexAttribPointer(material->GetShader()->GetAttributeHandle("a_vTexCoord"), 2, GL_FLOAT, GL_FALSE, meshVertexStride * sizeof(GLfloat), (void*)(meshVertexOffset * sizeof(GLfloat) + 2 * sizeof(GLfloat)));
		}
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);

		// render
		glDrawElements(mesh->GetRenderMode(), mesh->GetNumElements(), GL_UNSIGNED_INT, (void*)(meshIndexOffset * sizeof(GLint)));

		// cleanup
		glDisableVertexAttribArray(material->GetShader()->GetAttributeHandle("a_vPosition"));
		if (material->GetTexture() != NULL) {
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableVertexAttribArray(material->GetShader()->GetAttributeHandle("a_vTexCoord"));
		}
		glDisable(GL_BLEND);
		material->GetShader()->Unuse();
	}

	void RenderDevice::UpdateBuffers(std::vector<Mesh> meshes)
	{
		// generate the vertex buffer
		int vertexBufferSize = GetTotalVertexBufferLength(meshes);
		float* vertexBufferData = new float[vertexBufferSize];
		FillGlobalVertexBuffer(meshes, vertexBufferData);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize * sizeof(GLfloat), vertexBufferData, GL_STATIC_DRAW);
		delete[] vertexBufferData;

		// generate the index buffer
		int indexBufferSize = GetTotalIndexBufferLength(meshes);
		int* indexBufferData = new int[indexBufferSize];
		FillGlobalIndexBuffer(meshes, indexBufferData);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize * sizeof(GLint), indexBufferData, GL_STATIC_DRAW);
		delete[] indexBufferData;
	}
}