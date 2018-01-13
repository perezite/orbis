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
		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add bezier curve editor
		Entity* bcee = new Entity();
		BezierCurveEditor* editor = new BezierCurveEditor({ { -2.76923f,{ -0.50000f, -0.09125f } },{ -1.25000f,{ -0.14750f, 0.38625f } },{ 0.00000f,{ 0.17750f, -0.33125f } },{ -89.00006f,{ 0.50000f, -0.27625f } } });
		bcee->AddComponent(editor);
		AddEntity(bcee);


	}
}
