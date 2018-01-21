#include "Level8.h"

#include "../Controllers/TweenTester.h"
using namespace Controllers;

#include "../../Orbis/Components/TweenInspector.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Video/Texture.h"
#include "../../Orbis/Effects/Tween.h"
#include "../../Orbis/Core/DebugHelper.h"
using namespace Components;
using namespace Video;
using namespace Effects;
using namespace Core;

#include <iostream>
#include <algorithm>
#include <array>

namespace Levels
{
	Level8::Level8()
	{
		// add assets
		Texture* brickTex = new Texture("Textures/YellowBlock.png");
		Tween* tween = new Tween("Tweens/Test1.tween", 6.0f);

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add tweened brick
		Entity* brick = new Entity();
		AddEntity(TweenInspector::TryConstructEntity(tween));
		brick->AddComponent(new SpriteRenderer(brickTex));
		brick->AddComponent(new TweenTester(tween));
		AddEntity(brick);
	}
}
