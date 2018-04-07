#include "InputModeButtonController.h"

#include "SpriteController.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Core/LogHelper.h"
#include "../../Orbis/Game/Transform.h"
#include "../../Orbis/Game/Entity.h"
using namespace Input;
using namespace Core;
using namespace Game;
using namespace Math;

#include <algorithm>

namespace Controllers
{
	void InputModeButtonController::Update()
	{
		InputManager* inputManager = InputManager::GetInstance();

		if (inputManager->IsTapGoingDown(GetParent()->GetTransform()->GetRect()))
				Cycle();
	}

	void InputModeButtonController::Cycle()
	{
		// get new texture
		std::vector<Texture*>::iterator previousTextureIt = std::find(m_textures.begin(), m_textures.end(), m_Renderer->GetTexture());
		std::vector<Texture*>::iterator currentTextureIt = ++previousTextureIt;

		// update sprite renderer
		Texture* nextTexture = currentTextureIt != m_textures.end() ? (*currentTextureIt) : m_textures.front();
		m_Renderer->SetTexture(nextTexture);
	}
}