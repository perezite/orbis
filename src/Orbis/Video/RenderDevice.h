#pragma once

#include "RenderMode.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"
#include "Renderable.h"

#include "../Game/Transform.h"
#include "../Game/Entity.h"

#include "../../Base/Base.h"
using namespace base;

#include <vector>

namespace orb
{
	class RenderBatch
	{
	public:
		RenderBatch() : m_isDirty(false) { }

		void setRenderables(std::vector<Renderable*> renderables);

		std::vector<Renderable*> getRenderables() { return m_renderables; }

		void render();

	protected:
		void calculateIndices();

		void calculateVertices();

		std::vector<float> computeTransformedVertices(Renderable* renderable);

	private:
		std::vector<Renderable*> m_renderables;

		std::vector<GLushort> m_indices;

		std::vector<GLfloat> m_vertices;

		bool m_isDirty;
	};

	class RenderDevice
	{
	public:
		// ctor
		RenderDevice() : m_isDirty(false) { }

		// add a renderable
		void addRenderable(Renderable* renderable);

		// updateLevel a renderable
		void updateRenderable(Renderable* renderable);

		// delete a renderable
		void deleteRenderable(Renderable* renderable);

		// clear all renderables
		void clear();

		// render
		void render();

	protected:
		// update the batches
		void computeBatches();

		// prepare the rendering
		void prepareRendering();

		// finish the rendering
		void finishRendering();

	private:
		// the renderables
		std::vector<Renderable*> m_renderables;

		// the batches
		std::vector<RenderBatch> m_batches;

		// is the renderer in dirty state
		bool m_isDirty;
	};
}
