#include "Level8.h"

#include "../../Orbis/Components/BezierCurveEditor.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
using namespace Components;
using namespace Video;

#include <iostream>
#include <algorithm>
#include <array>

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
		bcve->AddComponent(new BezierCurveEditor());
		AddEntity(bcve);
	}
}
