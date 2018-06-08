#include "Level3.h"

#include "Level2.h"
#include "Level4.h"
#include "LevelHelper.h"

#include "../Controllers/DebugLineTester.h"
#include "../Controllers/WobbleController.h"
using namespace Controllers;

#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/RectangleRenderer.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Core/DebugHelper.h"
using namespace Video;
using namespace Components;
using namespace Core;

#include "../../Base/Math/MathHelper.h"
using namespace Math;

#include <iostream>

namespace Levels
{
	const int Level3::NUM_SPRITES = 1000;
	const float Level3::MIN_BLOCK_SCALE = 0.01f;
	const float Level3::MAX_BLOCK_SCALE = 0.05f;

	void Level3::Start()
	{
		// init textures
		std::vector<Texture*> textures;
		textures.push_back(VideoManager::GetInstance()->GetTexture("Textures/BlackBlock.png"));
		textures.push_back(VideoManager::GetInstance()->GetTexture("Textures/BlueBlock.png"));
		textures.push_back(VideoManager::GetInstance()->GetTexture("Textures/CyanBlock.png"));
		textures.push_back(VideoManager::GetInstance()->GetTexture("Textures/GreenBlock.png"));
		textures.push_back(VideoManager::GetInstance()->GetTexture("Textures/GreyBlock.png"));
		textures.push_back(VideoManager::GetInstance()->GetTexture("Textures/OrangeBlock.png"));
		textures.push_back(VideoManager::GetInstance()->GetTexture("Textures/PurpleBlock.png"));
		textures.push_back(VideoManager::GetInstance()->GetTexture("Textures/RedBlock.png"));
		textures.push_back(VideoManager::GetInstance()->GetTexture("Textures/VioletBlock.png"));
		textures.push_back(VideoManager::GetInstance()->GetTexture("Textures/YellowBlock.png"));

		// init camera
		Entity* camEntity = new Entity("Camera");
		camEntity->AddComponent(new Camera());
		AddEntity(camEntity);

		// init blocks
		for (unsigned int i = 0; i < NUM_SPRITES; i++)
		{
			static int counter = 0;
			bool hasTexture = ++counter % 2 == 0;

			Entity* entity = new Entity(hasTexture ? "Textured sprite" : "Solid sprite");
			Transform trans = Transform(Vector2D(MathHelper::GetRandom() - 0.5f, MathHelper::GetRandom() - 0.5f), 0.0f, Vector2D::One);
			entity->SetTransform(trans);

			Texture* texture = hasTexture ? textures[rand() % textures.size()] : NULL;
			entity->AddComponent(hasTexture ? (Component*)new SpriteRenderer(texture) : (Component*)new RectangleRenderer(Color(1.0f, 0.0f, 0.0f)));
			entity->AddComponent(new WobbleController());

			this->AddEntity(entity);
		}

		// add level switchers. Note: because we have no layering yet, the sprites above must be generated first in order to be batched in the right order
		LevelHelper::AddLevelSwitcher(this, new Level2(), false);
		LevelHelper::AddLevelSwitcher(this, new Level4(), true);

		// init debug line tester
		ORBIS_DEBUG (
			Entity* entity = new Entity("Debug line tester");
			entity->AddComponent(new DebugLineTester());
			AddEntity(entity);
		);
	}
}
