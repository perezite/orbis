#include "Level1.h"

#include "../../Orbis/Components/TriangleRenderer.h"
#include "../../Orbis/Components/TextureRenderer.h"
using namespace Components;

namespace Levels
{
	Level1::Level1()
	{
		// triangle entity
		Entity* triangle = new Entity();
		triangle->AddComponent(new TriangleRenderer());
		triangle->AddComponent(new TextureRenderer());
		this->AddEntity(triangle);
	}
}