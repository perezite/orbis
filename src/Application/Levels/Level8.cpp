#include "Level8.h"

#include "LevelUtil.h"
#include "Level7.h"
#include "Level9.h"

#include "../Controllers/WobbleBrickEffect.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

namespace app
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
		LevelUtil::addLevelSwitcher<Level7>(false);
		LevelUtil::addLevelSwitcher<Level9>(true);

		// add tweened brick
		Entity* brick = new Entity();
		brick->addComponent(new SpriteRenderer(brickTex));
		WobbleBrickEffect* wobbleBrickEffect = new WobbleBrickEffect(tween, 10.0f);
		brick->addComponent(wobbleBrickEffect);
		addEntity(brick);
	}
}
