#include "RenderDevice.h"

#include "VideoManager.h"
#include "Shader.h"
#include "Texture.h"
#include "RenderBatchHelper.h"

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
		for (unsigned int i = 0; i < m_renderBatches.size(); i++)
		{
			m_renderBatches.at(i).CalculateTransformedMeshes();
		}

		// refresh buffers
		if (m_isRefreshing)
		{
			RefreshBuffers(m_renderBatches);
			m_isRefreshing = false;
		}

		// update vertex buffer
		UpdateVertexBuffer(m_renderBatches);

		// render batches
		for (unsigned int i = 0; i < m_renderBatches.size(); i++)
		{
			RenderBatched(&m_renderBatches.at(i));
		}

		m_renderBatches.clear();
	}

	void RenderDevice::RenderBatched(RenderBatch* renderBatch)
	{
		Material* material = renderBatch->GetMaterial();

		// setup rendering
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// compute the mesh's buffer offsets
		int vboOffset = RenderBatchHelper::GetVertexBufferOffset(&m_renderBatches, renderBatch);
		int iboOffset = RenderBatchHelper::GetIndexBufferOffset(&m_renderBatches, renderBatch);
		int vertexStride = renderBatch->GetVertexStride();

		// setup shader
		material->GetShader()->Use();
		glEnableVertexAttribArray(material->GetShader()->GetAttributeHandle("a_vPosition"));
		glVertexAttribPointer(material->GetShader()->GetAttributeHandle("a_vPosition"), 2, GL_FLOAT, GL_FALSE, vertexStride * sizeof(GLfloat), (void*)(vboOffset * sizeof(GLfloat)));
		if (material->GetTexture() != NULL)
		{
			glVertexAttribPointer(material->GetShader()->GetAttributeHandle("a_vTexCoord"), 2, GL_FLOAT, GL_FALSE, vertexStride * sizeof(GLfloat), (void*)(vboOffset * sizeof(GLfloat) + 2 * sizeof(GLfloat)));
		}

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

		// render
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);
		glDrawElements(renderBatch->GetRenderMode(), renderBatch->GetNumIndices(), GL_UNSIGNED_INT, (void*)(iboOffset * sizeof(GLint)));

		// cleanup
		glDisableVertexAttribArray(material->GetShader()->GetAttributeHandle("a_vPosition"));
		if (material->GetTexture() != NULL) {
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableVertexAttribArray(material->GetShader()->GetAttributeHandle("a_vTexCoord"));
		}
		glDisable(GL_BLEND);
		material->GetShader()->Unuse();
	}

	void RenderDevice::UpdateVertexBuffer(std::vector<RenderBatch> batches)
	{
		int vertexBufferSize = RenderBatchHelper::GetVertexBufferLength(batches);
		float* vertexBufferData = new float[vertexBufferSize];
		RenderBatchHelper::FillVertexBufferData(batches, vertexBufferData);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexBufferSize * sizeof(GLfloat), vertexBufferData);
		delete[] vertexBufferData;
	}

	void RenderDevice::RefreshBuffers(std::vector<RenderBatch> batches)
	{
		// refresh vertex buffer size
		int vertexBufferSize = RenderBatchHelper::GetVertexBufferLength(batches);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferHandle);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize * sizeof(GLfloat), NULL, GL_DYNAMIC_DRAW);

		// refresh index buffer size and data
		int indexBufferSize = RenderBatchHelper::GetIndexBufferLength(batches);
		int* indexBufferData = new int[indexBufferSize];
		RenderBatchHelper::FillIndexBufferData(batches, indexBufferData);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize * sizeof(GLint), indexBufferData, GL_STATIC_DRAW);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexBufferSize * sizeof(GLint), indexBufferData);
		delete[] indexBufferData;
	}
}