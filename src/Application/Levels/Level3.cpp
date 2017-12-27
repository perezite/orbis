#include "Level3.h"

#include "../../Orbis/Video/Texture.h"
#include "../../Orbis/Components/RectangleRenderer.h"
#include "../../Orbis/Components/SpriteRenderer.h"

using namespace Video;

#include "../../Base/Math/MathHelper.h"
using namespace Math;

#include <iostream>

namespace Levels
{
	const int Level3::NUM_SPRITES = 1000;
	const float Level3::MIN_BLOCK_SCALE = 0.01f;
	const float Level3::MAX_BLOCK_SCALE = 0.05f;

	Level3::Level3()
	{
		std::vector<Texture*> textures;
		textures.push_back(new Texture("Textures/BlackBlock.png", true));
		textures.push_back(new Texture("Textures/BlueBlock.png", true));
		textures.push_back(new Texture("Textures/CyanBlock.png", true));
		textures.push_back(new Texture("Textures/GreenBlock.png", true));
		textures.push_back(new Texture("Textures/GreyBlock.png", true));
		textures.push_back(new Texture("Textures/OrangeBlock.png", true));
		textures.push_back(new Texture("Textures/PurpleBlock.png", true));
		textures.push_back(new Texture("Textures/RedBlock.png", true));
		textures.push_back(new Texture("Textures/VioletBlock.png", true));
		textures.push_back(new Texture("Textures/YellowBlock.png", true));	

		for (unsigned int i = 0; i < NUM_SPRITES; i++)
		{
			Entity* entity = new Entity();
			static int counter = 0;
			bool hasTexture = ++counter % 2 == 0;

			float scale = MIN_BLOCK_SCALE + (MAX_BLOCK_SCALE - MIN_BLOCK_SCALE) * MathHelper::GetRandom();
			Transform trans = Transform(Vector2D(MathHelper::GetRandom() - 0.5f, MathHelper::GetRandom() - 0.5f), 0.0f, Vector2D(scale, scale));
			entity->SetTransform(trans);

			Texture* texture = hasTexture ? textures[rand() % textures.size()] : NULL;
			entity->AddComponent(hasTexture ? (Renderer*)new SpriteRenderer(texture) : (Renderer*)new RectangleRenderer(Color(1.0f, 0.0f, 0.0f)));

			this->AddEntity(entity);
		}
	}
}
