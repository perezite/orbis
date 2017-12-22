#include "RenderBatchHelper.h"

#include "../../Base/System/Exception.h"	
using namespace System;

namespace Video
{
	int RenderBatchHelper::GetVertexBufferLength(std::vector<RenderBatch> batches)
	{
		int len = 0;
		for (unsigned int i = 0; i < batches.size(); i++)
		{
			len += batches.at(i).GetVertexBufferLength();
		}

		return len;
	}

	int RenderBatchHelper::GetIndexBufferLength(std::vector<RenderBatch> batches)
	{
		int len = 0;
		for (unsigned int i = 0; i < batches.size(); i++)
		{
			len += batches.at(i).GetIndexBufferLength();
		}

		return len;
	}

	void RenderBatchHelper::FillVertexBufferData(std::vector<RenderBatch> batches, float* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < batches.size(); i++)
		{
			batches.at(i).FillVertexBufferData(buffer + offset);
			offset += batches.at(i).GetVertexBufferLength();
		}
	}

	void RenderBatchHelper::FillIndexBufferData(std::vector<RenderBatch> batches, int* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < batches.size(); i++)
		{
			batches.at(i).FillIndexBufferData(buffer + offset);
			offset += batches.at(i).GetIndexBufferLength();
		}
	}

	int RenderBatchHelper::GetIndex(std::vector<RenderBatch>* batches, RenderBatch* const batch)
	{
		for (unsigned int i = 0; i < batches->size(); i++)
		{
			if (&batches->at(i) == batch)
				return i;
		}

		throw new Exception("RenderBatch was not found");
	}

	int RenderBatchHelper::GetVertexBufferOffset(std::vector<RenderBatch>* batches, RenderBatch* const batch)
	{
		int index = GetIndex(batches, batch);
		int offset = 0;
		for (int i = 0; i < index; i++)
		{
			offset += batches->at(i).GetVertexBufferLength();
		}

		return offset;
	}

	int RenderBatchHelper::GetIndexBufferOffset(std::vector<RenderBatch>* batches, RenderBatch* const batch)
	{
		int index = GetIndex(batches, batch);
		int offset = 0;
		for (int i = 0; i < index; i++)
		{
			offset += batches->at(i).GetIndexBufferLength();
		}
		return offset;
	}

	RenderBatch* RenderBatchHelper::FindMatchingRenderBatch(Mesh* mesh, Material* material, std::vector<RenderBatch>* batches)
	{
		for (unsigned int i = 0; i < batches->size(); i++)
		{
			RenderBatch batch = batches->at(i);
			if (*material == *batch.GetMaterial()
				&& mesh->GetVertexStride() == batch.GetVertexStride()
				&& mesh->GetRenderMode() == batch.GetRenderMode())
			{
				return &batches->at(i);
			}
		}

		return NULL;
	}
}