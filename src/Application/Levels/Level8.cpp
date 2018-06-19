#include "Level8.h"

#include "LevelHelper.h"
#include "Level7.h"
#include "Level9.h"

#include "../Controllers/TweenTester.h"
using namespace Controllers;

#include "../../Orbis/Components/TweenInspector.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Effects/EffectsManager.h"
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
	void Level8::start()
	{
		// add assets
		Texture* brickTex = VideoManager::getInstance()->getTexture("Textures/YellowBlock.png");
		Tween* tween = EffectsManager::getInstance()->GetTween("Tweens/Test1.tween");

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher<Level7>(this, false);
		LevelHelper::AddLevelSwitcher<Level9>(this, true);

		// add tweened brick
		Entity* brick = new Entity();
		AddEntity(TweenInspector::TryConstructEntity(this, tween));
		brick->AddComponent(new SpriteRenderer(brickTex));
		brick->AddComponent(new TweenTester(tween, 6.0f));
		AddEntity(brick);
	}
}
