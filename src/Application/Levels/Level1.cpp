#include "Level1.h"

#include "../../Orbis/Components/TriangleRenderer.h"
using namespace Components;

namespace Levels
{
	Level1::Level1()
	{
		// triangle entity
		Entity* triangle = new Entity();
		triangle->AddComponent(new TriangleRenderer());
		this->AddEntity(triangle);
	}
}