#pragma once

#include "RenderMode.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Material.h"

#include "../Game/Transform.h"
#include "../Game/Entity.h"
#include "../Components/Renderer.h"
#include "../Components/ParticleRenderer.h"
using namespace Game;
using namespace Components;

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Rect.h"
#include "../../Base/Math/Range.h"
using namespace Math;

#include <vector>

namespace Video
{
	typedef Range<unsigned int> BatchRange;

	class RenderDevice
	{
	public:
		// ctor
		RenderDevice()
			: m_isIndexArrayDirty(false)
		{}

		// add a renderer
		void AddRenderer(Renderer* renderer);

		// add a particle renderer
		void AddParticleRenderer(ParticleRenderer* particleRenderer);

		// update a renderer
		void UpdateRenderer(Renderer* renderer);

		// render
		void Render();

		// draw a debug line (slow!)
		void DrawDebugLine(Vector2D start, Vector2D end, Color color);

		// draw a debug rect (slow!)
		void DrawDebugRect(Rect rect, Color color);

	protected:
		// render batched
		void RenderBatched(std::vector<Renderer*> renderers, std::vector<GLfloat>& vertexArray, std::vector<GLuint>& indexArray, bool& indexArrayDirtyFlag);

		// update vertex array
		void UpdateVertexArray(std::vector<Renderer*> renderers, std::vector<GLfloat>& vertexArray);

		// update the vertex array for the renderer with the given index using the given mvp matrix
		void UpdateVertexArray(Renderer* const renderer, std::vector<GLfloat>& vertexArray, Matrix3& mvpMatrix);

		// reserver the vertex buffer to hold the renderer data
		void ReserveVertexArray(std::vector<Renderer*> renderers, std::vector<GLfloat>& vertexArray);

		// insert renderers indices at position in index array
		void UpdateIndexArray(std::vector<Renderer*> renderers, std::vector<GLuint>& indexArray, bool& dirtyFlag);

		// update the index array for the renderer at the given renderer index. The given offset is applied to the indices and an updated offset is returned
		void UpdateIndexArray(std::vector<Renderer*> renderers, std::vector<GLuint>& indexArray, unsigned int index, unsigned int& offset);

		// reserve index array space
		void ReserveIndexArray(std::vector<Renderer*> renderers, std::vector<GLuint>& indexArray);

		// compute the vao start index for a given batch
		unsigned int ComputeVaoStartIndex(std::vector<Renderer*> renderer, unsigned int batchIndex, std::vector<BatchRange> batches);

		// compute the batches
		std::vector<BatchRange> ComputeBatches(std::vector<Renderer*> renderers);

		// find index of first renderer in render batch
		template <class T>
		int FindFirstIndexInBatch(T* renderer, std::vector<T*> renderers);

		// draw a debug primitve
		void DrawDebugPrimitive(GLfloat* vertexArray, unsigned int vertexArraySize, Color color, RenderMode renderMode);

	private:
		// the vertex array
		std::vector<GLfloat> m_vertexArray;

		// the index array
		std::vector<GLuint> m_indexArray;

		// is the index array in dirty state
		bool m_isIndexArrayDirty;

		// the renderer components
		std::vector<Renderer*> m_renderers;

		// the particle vertex array
		std::vector<GLfloat> m_particleVertexArray;

		// the particle index array 
		std::vector<GLuint> m_particleIndexArray;

		// is the particle index array in dirty state
		bool m_isParticleIndexArrayDirty;

		// the particle renderer components
		std::vector<ParticleRenderer*> m_particleRenderers;
	};
}