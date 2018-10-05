#define OLD_STUFF

#ifdef OLD_STUFF

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
	typedef Range<unsigned int> BatchRange;

	class RenderDevice
	{
	public:
		// ctor
		RenderDevice()
			: m_isIndexArrayDirty(false)
		{}

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
		// updateLevel vertex array
		void updateVertexArray();

		// updateLevel the vertex array for the renderer with the given index using the given mvp matrix
		void insertIntoVertexArray(Renderable* const renderable, Matrix3& mvpMatrix);

		// reserver the vertex buffer to hold the renderer data
		void reserveVertexArray();

		// insert renderers indices at position in index array
		void updateIndexArray();

		// updateLevel the index array for the renderer at the given renderer index. The given offset is applied to the indices and an updated offset is returned
		void insertIntoIndexArray(unsigned int rendererIndex, unsigned short& offset);

		// reserve index array space
		void reserveIndexArray();

		// compute the vao start index for a given batch
		unsigned int computeVaoStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches);

		// compute the ibo (index buffer) start index for a given batch
		unsigned int computeIboStartIndex(unsigned int batchIndex, std::vector<BatchRange> batches);

		// compute the batches
		std::vector<BatchRange> computeBatches();

		// find index of first renderer in render batch
		int findFirstIndexInBatch(Renderable* renderable);

	private:
		// the vertex array
		std::vector<GLfloat> m_vertexArray;

		// the index array
		std::vector<GLushort> m_indexArray;

		// is the index array in dirty state
		bool m_isIndexArrayDirty;

		// the renderables
		std::vector<Renderable*> m_renderables;
	};
}

#endif

#ifdef NEW_STUFF

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
		void setRenderables(std::vector<Renderable*> renderables);

		std::vector<Renderable*> getRenderables() { return m_renderables; }

		void render();

	protected:
		void calculateIndices();

		void calculateVertices();

		std::vector<float> computeTransformedVertexes(Renderable* renderable);

	private:
		std::vector<Renderable*> m_renderables;

		std::vector<GLushort> m_indices;

		std::vector<GLfloat> m_vertices;

		Matrix3 m_worldCamMatrix;

		Matrix3 m_localCamMatrix;

		friend class RenderDevice;
	};

	class RenderDevice
	{
	public:
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

	private:
		// the renderalbes
		std::vector<Renderable*> m_renderables;

		// the batches
		std::vector<RenderBatch> m_batches;
	};
}

#endif