#include "Level8.h"

#include "LevelUtil.h"
#include "Level7.h"
#include "Level9.h"

#include "../Controllers/WobbleBrickEffect.h"
#include "../Inspectors/WobbleBrickEffectInspector.h"
using namespace controllers;
using namespace inspectors;

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
		LevelUtil::AddLevelSwitcher<Level7>(this, false);
		LevelUtil::AddLevelSwitcher<Level9>(this, true);

		// add tweened brick
		Entity* brick = new Entity();
		addEntity(TweenInspector::tryConstructEntity(this, tween));
		brick->addComponent(new SpriteRenderer(brickTex));
		WobbleBrickEffect* wobbleBrickEffect = new WobbleBrickEffect(tween, 6.0f);
		wobbleBrickEffect->SetInspector(new WobbleBrickEffectInspector());
		brick->addComponent(wobbleBrickEffect);
		addEntity(brick);
	}
}
