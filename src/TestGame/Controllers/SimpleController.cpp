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
	
		// compute delta position
		Vector2D deltaPosition = Vector2D(0.0f, 0.0f);
		if (inputManager->IsKeyDown(KeyCode::Left))
			deltaPosition = deltaPosition + Vector2D(-0.01f, 0.0f);
		if (inputManager->IsKeyDown(KeyCode::Right))
			deltaPosition = deltaPosition + Vector2D(0.01f, 0.0f);
		if (inputManager->IsKeyDown(KeyCode::Up))
			deltaPosition = deltaPosition + Vector2D(0.0f, 0.01f);
		if (inputManager->IsKeyDown(KeyCode::Down))
			deltaPosition = deltaPosition + Vector2D(0.0f, -0.01f);

		// compute delta rotation
		float deltaRotation = 0.0f;
		if (inputManager->IsKeyDown(KeyCode::a))
			deltaRotation = 0.1f;
		if (inputManager->IsKeyDown(KeyCode::s))
			deltaRotation = -0.1f;

		// apply
		Vector2D position = GetParent()->GetTransform()->GetPosition();
		float rotation = GetParent()->GetTransform()->GetRotation();
		GetParent()->GetTransform()->SetPosition(position + deltaPosition);
		GetParent()->GetTransform()->SetRotation(rotation + deltaRotation);

	}
}