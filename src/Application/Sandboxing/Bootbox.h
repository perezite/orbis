#pragma once

#define __SANDBOX__

#include "../../Orbis/Libraries/GL.h"
#include "../../Orbis/Game/Entity_v2.h"
using namespace Game;

#include <vector>

namespace Sandboxing
{
	// a class for bootstrapping code from the original sandbox class
	class Bootbox
	{
	public:
		static void Run();

	protected:
		static void InitGL();

		static void InitIndexArray();

		static void InitEntities();

		static void InitTextures();

		static void UpdateEntities();

		static void UpdateVertexArray();

		static int FindLastEntityByTexture(GLuint texture);

	private:
		static GLint m_positionHandle;
		static GLint m_texCoordHandle;
		static GLint m_samplerHandle;
		static std::vector<GLuint> m_textures;
		static std::vector<GLfloat> m_vertices;
		static std::vector<GLushort> m_indices;
		static std::vector<Entity_v2> m_entities;
		static const int NUM_SPRITES;
		static const int VERTICES_PER_SPRITE;
		static const int INDICES_PER_SPRITE;
		static const float MIN_BLOCK_EXTENT;
		static const float MAX_BLOCK_EXTENT;
	};
}