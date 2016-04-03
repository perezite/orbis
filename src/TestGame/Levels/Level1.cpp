#include "Level1.h"

#include "..\..\Orbis\Game\Entity.h"
using namespace Game;

#include "..\..\Orbis\Components\WireframeRenderer.h"
using namespace Components;

#include "..\Controllers\SimpleController.h"
using namespace Controllers;

#include <iostream>

namespace Levels
{
	Level1::Level1()
	{
		// entity 1
		Entity *entity1 = new Entity();
		entity1->AddComponent(new TestRenderer());
		entity1->AddComponent(new SimpleController());
		this->AddEntity(entity1);

		// entity 2
		Entity *entity2 = new Entity();
		entity2->AddComponent(new TestRenderer());
		entity2->AddComponent(new SimpleController());
		entity2->GetTransform()->SetPosition(Vector2D(0.5f, 0.5f));
		this->AddEntity(entity2);
	}
}