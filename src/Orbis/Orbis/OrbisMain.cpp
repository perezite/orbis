#include "OrbisMain.h"

#include "..\Game\Entity.h"
#include "..\Game\LevelManager.h"
using namespace Game;

#include "..\Components\TestRenderer.h"
using namespace Video;

#include <iostream>
#include <vector>

namespace Orbis
{
	const Vector2D OrbisMain::m_defaultWindowSize = Vector2D(640, 480);

	/*
	void OrbisMain::TestEntityController()
	{
		if (InputManager::GetInstance()->IsKeyDown(KeyCode::Left))
		{
			Transformation transformation = entity->GetTransformation();
			Vector2D position = transformation.GetPosition();
			Vector2D newPosition = Vector2D(position.GetX() - 0.01f, position.GetY());
			transformation.SetPosition(newPosition);
			entity->SetTransformation(transformation);
		}
	}*/

	OrbisMain::OrbisMain(int windowWidth, int windowHeight)
	{
		VideoManager::GetInstance()->SetWindowResolution((int)m_defaultWindowSize.GetX(), (int)m_defaultWindowSize.GetY());
	}

	void OrbisMain::QueueLevel(Level *level)
	{
		LevelManager::GetInstance()->QueueLevel(level);
	}

	void OrbisMain::Run()
	{
		InputManager *inputManager = InputManager::GetInstance();
		LevelManager *levelManager = LevelManager::GetInstance();
		bool hasQuitEvent = false;

		while (hasQuitEvent == false)
		{
			inputManager->Update();
			hasQuitEvent = inputManager->HasQuitEvent() || inputManager->IsKeyDown(KeyCode::Escape);

			levelManager->Update();
		}
	}
}