#include "RenderBatch.h"

namespace Video
{
	void RenderBatch::CalculateTransformedMeshes()
	{
		for (unsigned int i = 0; i < m_originalMeshes.size(); i++)
		{
			Mesh* mesh = m_originalMeshes[i];
			Transform transform = m_transforms[i];
			Mesh transformedMesh = mesh->Transformed(&transform);
			m_transformedMeshes.push_back(transformedMesh);
		}
	}

	int RenderBatch::GetVertexBufferLength()
	{
		int len = 0;
		for (unsigned int i = 0; i < m_transformedMeshes.size(); i++)
		{
			len += m_transformedMeshes[i].GetVertexBufferLength();
		}
		return len;
	}

	int RenderBatch::GetIndexBufferLength()
	{
		int len = 0;
		for (unsigned int i = 0; i < m_transformedMeshes.size(); i++)
		{
			len += m_transformedMeshes[i].GetIndexBufferLength();
		}
		return len;
	}

	int RenderBatch::GetVertexStride()
	{
		return m_transformedMeshes.at(0).GetVertexStride();
	}

	RenderMode RenderBatch::GetRenderMode()
	{
		return m_transformedMeshes.at(0).GetRenderMode();
	}

	int RenderBatch::GetNumIndices()
	{
		int num = 0;
		for (unsigned int i = 0; i < m_transformedMeshes.size(); i++)
		{
			num += m_transformedMeshes.at(i).GetIndices().size();
		}

		return num;
	}

	void RenderBatch::FillVertexBufferData(float* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < m_transformedMeshes.size(); i++)
		{
			m_transformedMeshes.at(i).FillVertexBufferData(buffer + offset);
			offset += m_transformedMeshes.at(i).GetVertexBufferLength();
		}
	}

	void RenderBatch::FillIndexBufferData(int* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < m_transformedMeshes.size(); i++)
		{
			m_transformedMeshes.at(i).FillIndexBufferData(buffer + offset);
			offset += m_transformedMeshes.at(i).GetIndexBufferLength();
		}
	}
}
