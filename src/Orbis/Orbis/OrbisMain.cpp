#include "OrbisMain.h"

#include "..\Game\Entity.h"
using namespace Game;

#include "..\Components\TestRenderer.h"
using namespace Video;

#include <iostream>
#include <vector>

namespace Orbis
{
	void OrbisMain::TestLevelInit()
	{
		Component *component = new TestRenderer(entity);
		entity->AddComponent(component);
		level->AddEntity(entity);
	}

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
	}

	OrbisMain::OrbisMain(int windowWidth, int windowHeight) :
		m_defaultWindowSize(Vector2D(640, 480))
	{
		VideoManager::GetInstance()->SetWindowResolution((int)m_defaultWindowSize.GetX(), (int)m_defaultWindowSize.GetY());

		// test
		level = new Level();
		entity = new Entity();
	}

	void OrbisMain::Run()
	{
		InputManager *inputManager = InputManager::GetInstance();
		bool hasQuitEvent = false;

		TestLevelInit();

		while (hasQuitEvent == false)
		{
			inputManager->Update();
			hasQuitEvent = inputManager->HasQuitEvent() || inputManager->IsKeyDown(KeyCode::Escape);

			TestEntityController();

			level->Update();
		}
	}
}