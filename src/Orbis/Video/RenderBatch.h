#pragma once

#include "Mesh.h"
#include "Material.h"
#include "RenderMode.h"

#include "../Game/Transform.h"
using namespace Game;

#include <vector>

namespace Video
{
	class RenderBatch
	{
	public:
		// ctor
		RenderBatch(const Transform& transform, Mesh* mesh, Material* material)
			: m_material(material)
		{
			m_transforms.push_back(transform);
			m_originalMeshes.push_back(mesh);
		}

		// get material
		Material* GetMaterial() const { return m_material; }

		// calculate transformed meshes
		void CalculateTransformedMeshes();

		// get transformed meshes
		std::vector<Mesh> GetTransformedMeshes() { return m_transformedMeshes; }

		// get length of the vertex buffer for this batch
		int GetVertexBufferLength();

		// get length of the index buffer for this batch
		int GetIndexBufferLength();

		// get the meshes vertex stride
		int GetVertexStride();

		// get the meshes render mode
		RenderMode GetRenderMode();

		// get the number of vertices
		int GetNumIndices();

		// fill the index buffer with the batch data
		void FillVertexBufferData(float* const buffer);

		// fill the index buffer with the batch data
		void FillIndexBufferData(int* const buffer);

	private:
		// the transforms
		std::vector<Transform> m_transforms;
		
		// meshes with applied transformation
		std::vector<Mesh> m_transformedMeshes;

		// the material
		Material* m_material;

		// the meshes
		std::vector<Mesh*> m_originalMeshes;
	};
}