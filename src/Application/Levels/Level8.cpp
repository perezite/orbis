#include "Level8.h"

#include "LevelHelper.h"
#include "Level7.h"
#include "Level9.h"

#include "../Controllers/TweenTester.h"
using namespace controllers;

#include "../../Orbis/Orbis.h"
using namespace orb::components;
using namespace orb::video;
using namespace orb::effects;
using namespace orb::core;

#include <iostream>
#include <algorithm>
#include <array>

namespace levels
{
	void Level8::start()
	{
		// add assets
		Texture* brickTex = VideoManager::getInstance()->getTexture("Textures/YellowBlock.png");
		Tween* tween = EffectsManager::getInstance()->getTween("Tweens/Test1.tween");

		// init camera
		Entity* cam = new Entity();
		cam->addComponent(new Camera());
		addEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher<Level7>(this, false);
		LevelHelper::AddLevelSwitcher<Level9>(this, true);

		// add tweened brick
		Entity* brick = new Entity();
		addEntity(TweenInspector::tryConstructEntity(this, tween));
		brick->addComponent(new SpriteRenderer(brickTex));
		brick->addComponent(new TweenTester(tween, 6.0f));
		addEntity(brick);
	}
}
