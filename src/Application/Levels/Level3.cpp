#include "Level3.h"

#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/MathHelper.h"
using namespace Components;
using namespace Math;
using namespace Video;

#include <math.h>

namespace
{
	// get random number in [0,1]
	float GetRandom()
	{
		float r = (float)(rand()) / (float)(RAND_MAX);
		return r;
	}
}

namespace Levels
{
	Level3::Level3()
	{
		// textures
		Texture* yellowBlockTexture = new Texture("Textures/YellowBlock.png");
		Texture* blueBlockTexture = new Texture("Textures/BlueBlock.png");

		// camera entity
		Entity* camera = new Entity();
		camera->AddComponent(new Camera());
		this->AddEntity(camera);

		// yellow block entity 1
		for (int i = 0; i < 1000; i++)
		{
			Vector2D pos = Vector2D(GetRandom() - 0.5f, GetRandom() - 0.5f);
			Entity* yellowBlock = new Entity("Yellow Brick");
			yellowBlock->AddComponent(new SpriteRenderer(yellowBlockTexture));
			yellowBlock->SetTransform(Transform(pos, 0.0f, Vector2D(0.33f, 0.33f)));
			this->AddEntity(yellowBlock);
		}
	}
}
