#include "Level5.h"

#include "LevelHelper.h"
#include "Level4.h"
#include "Level6.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Video/TextureAtlas.h"
using namespace Components;
using namespace Video;

namespace Levels
{
	void Level5::start()
	{
		// init textures
		Texture* yellowBlockTex = VideoManager::getInstance()->getTexture("Textures/YellowBlock.png");
		Texture* redBlockTex = VideoManager::getInstance()->getTexture("Textures/RedBlock.png");
		Texture* greenBlockTex = VideoManager::getInstance()->getTexture("Textures/GreenBlock.png");

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher<Level4>(this, false);
		LevelHelper::AddLevelSwitcher<Level6>(this, true);

		// init entities
		Entity* yellowBlock = new Entity("Yellow Brick");
		yellowBlock->AddComponent(new SpriteRenderer(yellowBlockTex));
		yellowBlock->SetTransform(Transform(Vector2D(-0.25f, 0.3f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(yellowBlock);

		Entity* redBlock = new Entity("Red Brick");
		redBlock->AddComponent(new SpriteRenderer(redBlockTex));
		redBlock->SetTransform(Transform(Vector2D(0.0f, 0.0f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(redBlock);

		Entity* greenBlock = new Entity("Green Brick");
		greenBlock->AddComponent(new SpriteRenderer(greenBlockTex));
		greenBlock->SetTransform(Transform(Vector2D(0.25f, 0.3f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(greenBlock);
	}
}
