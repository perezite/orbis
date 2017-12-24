#define __SANDBOX__

#include "../../Orbis/Libraries/GL.h"
#include "../../Orbis/Libraries/SDL.h"

#include <string>
#include <vector>

namespace Sandboxing
{
	struct STransform
	{
		float positionX;
		float positionY;
		float extent;
		bool isGrowing;
	};

	class Sandbox
	{
	public:
		static void Run();

	protected:
		static void Render();

		static void InitGL();

		static void InitIndexArray();

		static void UpdateVertexArray();

		static void InitTransforms();

		static void UpdateTransforms();
	private:
		static GLint m_positionHandle;
		static GLint m_texCoordHandle;
		static GLint m_samplerHandle;
		static GLuint m_texture;
		static std::vector<GLfloat> m_vertices;
		static std::vector<GLushort> m_indices;
		static std::vector<STransform> m_transforms;
		static const int NUM_SPRITES;
		static const int VERTICES_PER_SPRITE;
		static const int INDICES_PER_SPRITE;
		static const int SPRITES_PER_BATCH;
		static const float MIN_BLOCK_EXTENT;
		static const float MAX_BLOCK_EXTENT;
	};

}
