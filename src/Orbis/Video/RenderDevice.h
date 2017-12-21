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
#include <tuple>

namespace Video
{
	class RenderDevice
	{
	public:
		// ctor
		RenderDevice();

		// dtor
		virtual ~RenderDevice();

		// begin
		void Begin();

		// render
		void Render(Transform* transform, Mesh* mesh, Material* material);

		// finalize
		void Finalize();

		// refresh the device
		void Refresh() { m_isRefreshing = true; }

	protected:
		// render single data
		void RenderSingle(Transform* transform, Mesh* mesh, Material* material, std::vector<Mesh>* meshList);

		// update vertex buffer
		void UpdateVertexBuffer(std::vector<Mesh> meshes);

		// update index buffer
		void RefreshBuffers(std::vector<Mesh> meshes);

	private:
		// the data to be rendered
		std::vector<std::tuple<Transform, Mesh*, Material*>> m_renderData;

		// the vertex buffer object
		GLuint m_vertexBufferHandle;

		// the index buffer object
		GLuint m_indexBufferHandle;

		// is the device refreshing
		bool m_isRefreshing;
	};
}