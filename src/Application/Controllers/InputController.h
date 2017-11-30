#pragma once

#include "SpriteController.h"

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/Texture.h"
using namespace Components;
using namespace Video;

#include <vector>

namespace Controllers
{
	class InputController : public Component 
	{
	public:
		// update
		void Update();

		// set available textures for input mode overlay
		void SetInputModeOverlayTextures(std::vector<Texture*> inputModeOverlayTextures) { m_inputModeOverlayTextures = inputModeOverlayTextures; }

		// set the input mode overlay sprite renderer
		void SetInputModeOverlaySpriteRenderer(SpriteRenderer* const spriteRenderer) { m_inputModeOverlaySpriteRenderer = spriteRenderer; }

		// set yellow brick
		void SetYellowBlock(SpriteController* const yellowBrick) { m_yellowBrick = yellowBrick; }

		// set blue brick
		void SetBlueBrick(SpriteController* const blueBrick) { m_blueBrick = blueBrick; }
	protected:
		// affect the currently selected entity
		void Affect(bool positive);

		// cycle through the input modes
		void Cycle();

	private:
		// input mode overlay sprite renderer
		SpriteRenderer* m_inputModeOverlaySpriteRenderer;

		// available input mode overlay textures
		std::vector<Texture*> m_inputModeOverlayTextures;

		// the yellow brick
		SpriteController* m_yellowBrick;

		// the blue brick
		SpriteController* m_blueBrick;
	};
}