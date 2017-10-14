#include "Level1.h"

#include "../../Orbis/Components/SpriteRenderer.h"
using namespace Components;

namespace Levels
{
	Level1::Level1()
	{
		// sprite entity
		Entity* sprite = new Entity();
		sprite->AddComponent(new SpriteRenderer());
		this->AddEntity(sprite);
	}
}