#pragma once

#include "Mesh.h"

#include <vector>

namespace Video
{
	class MeshHelper
	{
	public: 
		// get the total vertex buffer length of a mesh list
		static int GetVertexBufferLength(std::vector<Mesh> meshes);

		// get the total index buffer length of a mesh list
		static int GetIndexBufferLength(std::vector<Mesh> meshes);

		// fills a preallocated buffer with a mesh list's vertex data
		static void FillVertexBufferData(std::vector<Mesh> meshes, float* const buffer);

		// fills a preallocated buffer with a mesh list's index data
		static void FillIndexBufferData(std::vector<Mesh> meshes, int* const buffer);

		// get the index of a mesh within the mesh list
		static int GetMeshIndex(std::vector<Mesh>* meshes, Mesh* const mesh);

		// get the vertex buffer offset for a given mesh
		static int GetMeshVertexOffset(std::vector<Mesh>* meshes, Mesh* const mesh);

		// get the index buffer offset for a given mesh
		static int GetMeshIndexOffset(std::vector<Mesh>* meshes, Mesh* const mesh);
	};
}