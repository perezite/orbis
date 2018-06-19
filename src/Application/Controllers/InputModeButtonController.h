#pragma once

#include "SpriteController.h"
#include "CameraController.h"

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/Texture.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Game/Transform.h"
using namespace Components;
using namespace Video;
using namespace Game;

#include <string>
#include <vector>
#include <map>

namespace Controllers
{
	class InputModeButtonController : public Component 
	{
	public:
		// ctor
		InputModeButtonController(SpriteRenderer* spriteRenderer, std::vector<Texture*> inputModeTextures)
			: m_Renderer(spriteRenderer), m_textures(inputModeTextures)
		{}

		// update
		void update();

	protected:
		// cycle through the input modes
		void Cycle();

	private:
		// input mode overlay sprite renderer
		SpriteRenderer* m_Renderer;

		// available input mode overlay textures
		std::vector<Texture*> m_textures;

		// initial transforms of the entites
		std::map<Entity*, Transform> m_initialTransforms;
	};
}