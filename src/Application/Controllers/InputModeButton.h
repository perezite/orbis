#pragma once

#include "SpriteController.h"
#include "CameraBehavior.h"

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/Texture.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Game/Transform.h"
using namespace orb::components;
using namespace orb::video;
using namespace orb::game;

#include <string>
#include <vector>
#include <map>

namespace controllers
{
	class InputModeButton : public Component 
	{
	public:
		// ctor
		InputModeButton(SpriteRenderer* spriteRenderer, std::vector<Texture*> inputModeTextures)
			: m_renderer(spriteRenderer), m_textures(inputModeTextures)
		{}

		// update
		void update();

	protected:
		// cycle through the input modes
		void cycle();

	private:
		// input mode overlay sprite renderer
		SpriteRenderer* m_renderer;

		// available input mode overlay textures
		std::vector<Texture*> m_textures;

		// initial transforms of the entites
		std::map<Entity*, Transform> m_initialTransforms;
	};
}