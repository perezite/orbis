#pragma once

#define __SANDBOX__

#include "../../Orbis/Libraries/GL.h"
#include "../../Orbis/Game/Entity_v2.h"
#include "../../Orbis/Video/Shader_v2.h"
#include "../../Orbis/Video/Texture.h"
using namespace Game;
using namespace Video;

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

		static void AddEntity(Entity_v2* entity);

		static int FindLastBatchEntityByTexture(Texture* texture);

		static void Close();

	private:
		static Shader_v2* m_shader;
		static std::vector<Texture*> m_textures;
		static std::vector<Entity_v2> m_entities;
		static const int NUM_SPRITES;
		static const float MIN_BLOCK_SCALE;
		static const float MAX_BLOCK_SCALE;
	};
}