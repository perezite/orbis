#include "Level8.h"

#include "../../Orbis/Components/BezierCurveEditor.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Video/Texture.h"
using namespace Components;
using namespace Video;

#include <iostream>
#include <algorithm>
#include <array>

namespace Levels
{
	Level8::Level8()
	{
		// init textures
		Texture* coordSystemTex = new Texture("Textures/CoordinateSystem2.png");

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// the bezier curve coordinate system
		Entity* bccse = new Entity();
		bccse->AddComponent(new SpriteRenderer(coordSystemTex));
		AddEntity(bccse);

		// add bezier curve editor
		Entity* bcve = new Entity();
		bcve->AddComponent(new BezierCurveEditor());
		AddEntity(bcve);
	}
}
