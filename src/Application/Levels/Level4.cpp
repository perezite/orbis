#include "Level4.h"

#include "../Controllers/BinPackingVisualizer.h"
using namespace Controllers;

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
using namespace Components;
using namespace Video;

namespace Levels
{
	Level4::Level4()
	{
		VideoManager::GetInstance()->SetResolution(Vector2D(800, 800));

		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		Entity* visualizer = new Entity();
		visualizer->AddComponent(new BinPackingVisualizer());
		AddEntity(visualizer);
	}
}
