#include "MeshHelper.h"

#include "../../Base/System/Exception.h"	
using namespace System;

namespace Video
{
	// get the total vertex buffer length of a mesh list
	int MeshHelper::GetVertexBufferLength(std::vector<Mesh> meshes)
	{
		int len = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			len += meshes.at(i).GetVertexBufferLength();
		}

		return len;
	}

	// get the total index buffer length of a mesh list
	int MeshHelper::GetIndexBufferLength(std::vector<Mesh> meshes)
	{
		int len = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			len += meshes.at(i).GetIndexBufferLength();
		}

		return len;
	}

	// fills a preallocated buffer with a mesh list's vertex data
	void MeshHelper::FillVertexBufferData(std::vector<Mesh> meshes, float* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes.at(i).FillVertexBuffer(buffer + offset);
			offset += meshes.at(i).GetVertexBufferLength();
		}
	}

	// fills a preallocated buffer with a mesh list's index data
	void MeshHelper::FillIndexBufferData(std::vector<Mesh> meshes, int* const buffer)
	{
		unsigned int offset = 0;
		for (unsigned int i = 0; i < meshes.size(); i++)
		{
			meshes.at(i).FillIndexBuffer(buffer + offset);
			offset += meshes.at(i).GetIndexBufferLength();
		}
	}

	// get the index of a mesh within the mesh list
	int MeshHelper::GetMeshIndex(std::vector<Mesh>* meshes, Mesh* const mesh)
	{
		for (unsigned int i = 0; i < meshes->size(); i++)
		{
			if (&meshes->at(i) == mesh)
				return i;
		}

		throw new Exception("Mesh was not found");
	}

	// get the vertex buffer offset for a given mesh
	int MeshHelper::GetMeshVertexOffset(std::vector<Mesh>* meshes, Mesh* const mesh)
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
	int MeshHelper::GetMeshIndexOffset(std::vector<Mesh>* meshes, Mesh* const mesh)
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