#include "Level6.h"

#include "LevelHelper.h"
#include "Level5.h"
#include "Level7.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Video/TextureAtlas.h"
using namespace components;
using namespace video;

namespace levels
{
	void Level6::start()
	{
		// init textures
		Texture* bleedingTestBlue = VideoManager::getInstance()->getTexture("Textures/BleedingTestBlue.png");
		Texture* bleedingTestGreen = VideoManager::getInstance()->getTexture("Textures/BleedingTestGreen.png");
		Texture* bleedingTestRed = VideoManager::getInstance()->getTexture("Textures/BleedingTestRed.png");
		Texture* bleedingTestYellow = VideoManager::getInstance()->getTexture("Textures/BleedingTestYellow.png");

		// init camera
		Entity* cam = new Entity();
		cam->addComponent(new Camera());
		addEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher<Level5>(this, false);
		LevelHelper::AddLevelSwitcher<Level7>(this, true);

		// init entities
		Entity* blueEntity = new Entity("Bleeding Test Blue");
		blueEntity->addComponent(new SpriteRenderer(bleedingTestBlue));
		blueEntity->setTransform(Transform(Vector2D(-0.25f, -0.25f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(blueEntity);

		Entity* greenEntity = new Entity("Bleeding Test Green");
		greenEntity->addComponent(new SpriteRenderer(bleedingTestGreen));
		greenEntity->setTransform(Transform(Vector2D(0.25f, -0.25f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(greenEntity);

		Entity* redEntity = new Entity("Bleeding Test Red");
		redEntity->addComponent(new SpriteRenderer(bleedingTestRed));
		redEntity->setTransform(Transform(Vector2D(0.25f, 0.25f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(redEntity);

		Entity* yellowEntity = new Entity("Bleeding Test Yellow");
		yellowEntity->addComponent(new SpriteRenderer(bleedingTestYellow));
		yellowEntity->setTransform(Transform(Vector2D(-0.25f, 0.25f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->addEntity(yellowEntity);
	}
}
