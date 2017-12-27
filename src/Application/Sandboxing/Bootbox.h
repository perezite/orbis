// #define __SANDBOX__

#pragma once

#include "../../Orbis/Libraries/GL.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Video/Shader.h"
#include "../../Orbis/Video/Texture.h"
#include "../../Orbis/Components/Camera.h"
using namespace Game;
using namespace Video;
using namespace Components;

#include <vector>

namespace Sandboxing
{
	// a class for bootstrapping code from the original sandbox class
	class Bootbox
	{
	public:
		static void Run();

	protected:

		static void Init();

		static void StartEntities();

		static void InitEntities();

		static void InitTextures();

		static void UpdateEntities();

		static void Close();

	private:
		static std::vector<Texture*> m_textures;
		static std::vector<Entity*> m_entities;
		static const int NUM_SPRITES;
		static const float MIN_BLOCK_SCALE;
		static const float MAX_BLOCK_SCALE;
	};
}

void Bootbox_Dummy();
