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

		static int FindLastBatchEntityByTexture(GLuint texture);

	private:
		static GLint m_positionHandle;
		static GLint m_texCoordHandle;
		static GLint m_samplerHandle;
		static std::vector<GLuint> m_textures;
		static std::vector<Entity_v2> m_entities;
		static const int NUM_SPRITES;
		static const float MIN_BLOCK_SCALE;
		static const float MAX_BLOCK_SCALE;
	};
}