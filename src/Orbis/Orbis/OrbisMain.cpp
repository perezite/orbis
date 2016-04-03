#include "OrbisMain.h"

#include "..\Game\Entity.h"
#include "..\Game\LevelManager.h"
using namespace Game;

#include "..\Components\WireframeRenderer.h"
using namespace Video;

#include <iostream>
#include <vector>


namespace Orbis
{
	const Vector2D OrbisMain::m_defaultWindowSize = Vector2D(480, 480);

	OrbisMain::OrbisMain(int windowWidth, int windowHeight)
	{
		VideoManager::GetInstance()->SetWindowResolution((int)m_defaultWindowSize.GetX(), (int)m_defaultWindowSize.GetY());
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