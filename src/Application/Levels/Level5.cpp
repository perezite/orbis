#include "Level5.h"

#include "LevelHelper.h"
#include "Level4.h"
#include "Level6.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Video/TextureAtlas.h"
using namespace components;
using namespace video;

namespace levels
{
	void Level5::start()
	{
		// init textures
		Texture* yellowBlockTex = VideoManager::getInstance()->getTexture("Textures/YellowBlock.png");
		Texture* redBlockTex = VideoManager::getInstance()->getTexture("Textures/RedBlock.png");
		Texture* greenBlockTex = VideoManager::getInstance()->getTexture("Textures/GreenBlock.png");

		// init camera
		Entity* cam = new Entity();
		cam->addComponent(new Camera());
		addEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher<Level4>(this, false);
		LevelHelper::AddLevelSwitcher<Level6>(this, true);

		// init entities
		Entity* yellowBlock = new Entity("Yellow Brick");
		yellowBlock->addComponent(new SpriteRenderer(yellowBlockTex));
		yellowBlock->setTransform(Transform(Vector2D(-0.25f, 0.3f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(yellowBlock);

		Entity* redBlock = new Entity("Red Brick");
		redBlock->addComponent(new SpriteRenderer(redBlockTex));
		redBlock->setTransform(Transform(Vector2D(0.0f, 0.0f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(redBlock);

		Entity* greenBlock = new Entity("Green Brick");
		greenBlock->addComponent(new SpriteRenderer(greenBlockTex));
		greenBlock->setTransform(Transform(Vector2D(0.25f, 0.3f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(greenBlock);
	}
}
