#include "OrbisMain.h"

#include "..\Game\Entity.h"
#include "..\Game\LevelManager.h"
using namespace Game;

#include "..\Components\SillyRenderer.h"
using namespace Video;

#include <iostream>
#include <vector>

namespace Orbis
{
	const Vector2D OrbisMain::m_defaultWindowSize = Vector2D(480, 480);

	OrbisMain::OrbisMain(int windowWidth = (int)m_defaultWindowSize.GetX(), int windowHeight = (int)m_defaultWindowSize.GetY())
	{
		VideoManager::GetInstance()->SetWindowResolution(windowWidth, windowHeight);
	}

	void OrbisMain::Run()
	{
		InputManager *inputManager = InputManager::GetInstance();
		LevelManager *levelManager = LevelManager::GetInstance();
		bool hasQuitEvent = false;

		while (hasQuitEvent == false)
		{
			inputManager->Update();
			hasQuitEvent = inputManager->HasQuitEvent();

			levelManager->Update();
		}
	}
}