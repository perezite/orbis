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

		// temp
		std::vector<float> test = { 1.0f, 2.0f, 3.0f };
		std::pair<float, float> test2 = {1.0f, 1.0f};

		// add bezier curve editor
		Entity* bcee = new Entity();
		BezierCurveEditor* editor = new BezierCurveEditor({ { -1.31818f,{ -0.45250f, 0.49125f } },{ 0.00000f,{ -0.05750f, 0.12625f } },{ 0.00000f,{ 0.15750f, 0.41125f } },{ 0.00000f,{ 0.38750f, 0.11375f } } });
		bcee->AddComponent(editor);
		AddEntity(bcee);
	}
}
