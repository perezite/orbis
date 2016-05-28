#include "Level1.h"

#include "..\..\Orbis\Game\Entity.h"
using namespace Game;

#include "..\..\Orbis\Components\SillyRenderer.h"
using namespace Components;

#include "..\..\Orbis\Components\Camera.h"
using namespace Components;

#include "..\Controllers\SimpleController.h"
#include "..\Controllers\\CameraController.h"
using namespace Controllers;

#include <iostream>

namespace Levels
{
	Level1::Level1()
	{
		// camera
		Entity *camera = new Entity();
		camera->AddComponent(new Camera());
		camera->AddComponent(new CameraController());
		camera->GetTransform()->SetScale(Vector2D(4.0f, 4.0f));
		this->AddEntity(camera);

		// entity 1
		Entity *entity1 = new Entity();
		entity1->GetTransform()->SetScale(Vector2D(0.5f, 0.5f));
		entity1->AddComponent(new SillyRenderer());
		entity1->AddComponent(new SimpleController());
		this->AddEntity(entity1);

		// entity 2
		Entity *entity2 = new Entity();
		entity2->GetTransform()->SetScale(Vector2D(1.0f, 0.5f));
		entity2->AddComponent(new SillyRenderer());
		entity2->AddComponent(new SimpleController());
		entity2->GetTransform()->SetPosition(Vector2D(1.0f, 2.0f));
		this->AddEntity(entity2);
	}
}