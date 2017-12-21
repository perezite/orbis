#pragma once

#include "RenderMode.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include "RenderBatch.h"

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
		// render a batch
		void RenderBatched(RenderBatch* renderBatch);

		// update vertex buffer
		void UpdateVertexBuffer(std::vector<RenderBatch> batches);

		// update index buffer
		void RefreshBuffers(std::vector<RenderBatch> batches);

	private:
		// the render batches
		std::vector<RenderBatch> m_renderBatches;

		// the vertex buffer object
		GLuint m_vertexBufferHandle;

		// the index buffer object
		GLuint m_indexBufferHandle;

		// is the device refreshing
		bool m_isRefreshing;
	};
}