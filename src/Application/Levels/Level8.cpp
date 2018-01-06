#include "Level8.h"

#include "../Controllers/BezierCurveVisualizer.h"
using namespace Controllers;

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
using namespace Components;
using namespace Video;

namespace Levels
{
	Level8::Level8()
	{
		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add bezier curve visualizer
		Entity* bcve = new Entity();
		bcve->AddComponent(new BezierCurveVisualizer());
		AddEntity(bcve);
	}
}
