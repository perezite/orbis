#include "Level3.h"

#include "Level2.h"
#include "Level4.h"
#include "LevelUtil.h"

#include "../Controllers/DebugLineTester.h"
#include "../Controllers/WobbleController.h"
using namespace controllers;

#include "../../Orbis/Orbis.h"
using namespace orb::video;
using namespace orb::components;
using namespace orb::core;

#include "../../Base/Math/Math.h"
using namespace base::math;

#include <iostream>

namespace levels
{
	const int Level3::NUM_SPRITES = 1000;
	const float Level3::MIN_BLOCK_SCALE = 0.01f;
	const float Level3::MAX_BLOCK_SCALE = 0.05f;

	void Level3::start()
	{
		// init textures
		std::vector<Texture*> textures;
		textures.push_back(VideoManager::getInstance()->getTexture("Textures/BlackBlock.png"));
		textures.push_back(VideoManager::getInstance()->getTexture("Textures/BlueBlock.png"));
		textures.push_back(VideoManager::getInstance()->getTexture("Textures/CyanBlock.png"));
		textures.push_back(VideoManager::getInstance()->getTexture("Textures/GreenBlock.png"));
		textures.push_back(VideoManager::getInstance()->getTexture("Textures/GreyBlock.png"));
		textures.push_back(VideoManager::getInstance()->getTexture("Textures/OrangeBlock.png"));
		textures.push_back(VideoManager::getInstance()->getTexture("Textures/PurpleBlock.png"));
		textures.push_back(VideoManager::getInstance()->getTexture("Textures/RedBlock.png"));
		textures.push_back(VideoManager::getInstance()->getTexture("Textures/VioletBlock.png"));
		textures.push_back(VideoManager::getInstance()->getTexture("Textures/YellowBlock.png"));

		// init camera
		Entity* camEntity = new Entity("Camera");
		camEntity->addComponent(new Camera());
		addEntity(camEntity);

		// init blocks
		for (unsigned int i = 0; i < NUM_SPRITES; i++)
		{
			static int counter = 0;
			bool hasTexture = ++counter % 2 == 0;

			Entity* entity = new Entity(hasTexture ? "Textured sprite" : "Solid sprite");
			Transform trans = Transform(Vector2D(Math::getRandom() - 0.5f, Math::getRandom() - 0.5f), 0.0f, Vector2D::One);
			entity->setTransform(trans);

			Texture* texture = hasTexture ? textures[rand() % textures.size()] : NULL;
			entity->addComponent(hasTexture ? (Component*)new SpriteRenderer(texture) : (Component*)new RectangleRenderer(Color(1.0f, 0.0f, 0.0f)));
			entity->addComponent(new WobbleController());

			this->addEntity(entity);
		}

		// add level switchers. Note: because we have no layering yet, the sprites above must be generated first in order to be batched in the right order
		LevelUtil::AddLevelSwitcher<Level2>(this, false);
		LevelUtil::AddLevelSwitcher<Level4>(this, true);

		// init debug line tester
		ORBIS_DEBUG (
			Entity* entity = new Entity("Debug line tester");
			entity->addComponent(new DebugLineTester());
			addEntity(entity);
		);
	}
}
