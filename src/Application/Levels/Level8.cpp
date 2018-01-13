#include "Level8.h"

#include "../Controllers/BezierCurveTester.h"
using namespace Controllers;

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
		// add texture
		Texture* brickTex = new Texture("Textures/YellowBlock.png");

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add editor for the tweened brick
		BezierCurve brickCurve = BezierCurve(
			{ { 9.99999f,{ 0.00000f, 0.00875f } },{ -2.66667f,{ 0.03000f, 0.99125f } },{ 1.31818f,{ 0.31000f, 0.05875f } },{ -0.77778f,{ 0.50000f, 0.49625f } },{ -0.35897f,{ 0.70250f, 0.08125f } },{ -0.05405f,{ 1.00000f, 0.03875f } } }
		);
		if (false)
		{
			Entity* bcee = new Entity();
			BezierCurveEditor* editor = new BezierCurveEditor(brickCurve);
			bcee->AddComponent(editor);
			AddEntity(bcee);
		}

		// add tweened brick
		Entity* brick = new Entity();
		brick->AddComponent(new SpriteRenderer(brickTex));
		brick->AddComponent(new BezierCurveTester(brickCurve, 6.0f));
		AddEntity(brick);

	}
}
