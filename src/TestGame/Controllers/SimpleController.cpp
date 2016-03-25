#include "SimpleController.h"

#include "..\..\Orbis\Game\Entity.h"
using namespace Game;

#include "..\..\Orbis\Input\InputManager.h"
using namespace Input;

namespace Controllers
{
	void SimpleController::Update() 
	{
		InputManager* inputManager = InputManager::GetInstance();
	
		Vector2D offset = Vector2D(0.0f, 0.0f);
		if (inputManager->IsKeyDown(KeyCode::Left))
			offset = offset + Vector2D(-0.01f, 0.0f);
		if (inputManager->IsKeyDown(KeyCode::Right))
			offset = offset + Vector2D(0.01f, 0.0f);
		if (inputManager->IsKeyDown(KeyCode::Up))
			offset = offset + Vector2D(0.0f, 0.01f);
		if (inputManager->IsKeyDown(KeyCode::Down))
			offset = offset + Vector2D(0.0f, -0.01f);

		Vector2D position = GetParent()->GetTransform()->GetPosition();
		GetParent()->GetTransform()->SetPosition(position + offset);
	}
}