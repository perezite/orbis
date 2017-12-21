#include "RenderDevice.h"

#include "VideoManager.h"
#include "Shader.h"
#include "Texture.h"
#include "MeshHelper.h"
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

namespace Video
{
	RenderDevice::RenderDevice() :
		m_vertexBufferHandle(0), m_indexBufferHandle(0), m_isRefreshing(false)
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
		m_renderBatches.clear();
	}

	void RenderDevice::Render(Transform* transform, Mesh* mesh, Material* material)
	{
		m_renderBatches.push_back(RenderBatch(*transform, mesh, material));
	}

	void RenderDevice::Finalize()
	{
		// compute transformed meshes
		std::vector<Mesh> transformedMeshes;
		for (unsigned int i = 0; i < m_renderBatches.size(); i++)
		{
			RenderBatch batch = m_renderBatches[i];
			Mesh transformedMesh = batch.GetMesh()->Transformed(&batch.GetTransform());
			transformedMeshes.push_back(transformedMesh);
		}

		// update buffers
		UpdateVertexBuffer(transformedMeshes);
		if (m_isRefreshing)
		{
			RefreshBuffers(transformedMeshes);
			m_isRefreshing = false;
		}

		// render batches
		for (unsigned int i = 0; i < m_renderBatches.size(); i++)
		{
			RenderBatch batch = m_renderBatches[i];
			RenderSingle(&batch.GetTransform(), &transformedMeshes[i], batch.GetMaterial(), &transformedMeshes);
		}
	}

	void RenderDevice::RenderSingle(const Transform* transform, Mesh* mesh, Material* material, std::vector<Mesh>* meshList)
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
		int meshVertexOffset = MeshHelper::GetMeshVertexOffset(meshList, mesh);
		int meshVertexStride = mesh->GetVertexStride();
		int meshIndexOffset = MeshHelper::GetMeshIndexOffset(meshList, mesh);

		// prepare render
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);
		glVertexAttribPointer(material->GetShader()->GetAttributeHandle("a_vPosition"), 2, GL_FLOAT, GL_FALSE, meshVertexStride * sizeof(GLfloat), (void*)(meshVertexOffset * sizeof(GLfloat)));
		if (material->GetTexture() != NULL)
		{
			glVertexAttribPointer(material->GetShader()->GetAttributeHandle("a_vTexCoord"), 2, GL_FLOAT, GL_FALSE, meshVertexStride * sizeof(GLfloat), (void*)(meshVertexOffset * sizeof(GLfloat) + 2 * sizeof(GLfloat)));
		}

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

	void RenderDevice::UpdateVertexBuffer(std::vector<Mesh> meshes)
	{
		int vertexBufferSize = MeshHelper::GetVertexBufferLength(meshes);
		float* vertexBufferData = new float[vertexBufferSize];
		MeshHelper::FillVertexBufferData(meshes, vertexBufferData);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexBufferSize * sizeof(GLfloat), vertexBufferData);
		delete[] vertexBufferData;
	}

	void RenderDevice::RefreshBuffers(std::vector<Mesh> meshes)
	{
		// refresh vertex buffer size
		int vertexBufferSize = MeshHelper::GetVertexBufferLength(meshes);
		float* vertexBufferData = new float[vertexBufferSize];
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

		// refresh index buffer size and data
		int indexBufferSize = MeshHelper::GetIndexBufferLength(meshes);
		int* indexBufferData = new int[indexBufferSize];
		MeshHelper::FillIndexBufferData(meshes, indexBufferData);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize * sizeof(GLint), indexBufferData, GL_STATIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexBufferSize * sizeof(GLint), indexBufferData);
		delete[] indexBufferData;
	}
}