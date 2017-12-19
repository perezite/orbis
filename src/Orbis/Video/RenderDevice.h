#pragma once

#include "RenderMode.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"

#include "../Game/Transform.h"
using namespace Game;

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include <vector>

namespace Video
{
	class RenderDevice
	{
	public:
		// ctor
		RenderDevice();

		// dtor
		virtual ~RenderDevice();

		// add a mesh to the renderer
		void AddMesh(Mesh* const mesh);

		// initialize the buffers
		void InitializeBuffers();

		// render
		void Render(Transform* transform, Mesh* mesh, Material* material);

	private:
		// the meshes used in the renderer
		std::vector<Mesh*> m_meshes;

		// the vertex buffer object
		GLuint m_vertexBufferHandle;

		// the index buffer object
		GLuint m_indexBufferHandle;

		// are the vertex and index buffers initialized
		bool m_areBuffersInitialized;
	};
}