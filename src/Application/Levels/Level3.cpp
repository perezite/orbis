#include "Level3.h"

#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/MathHelper.h"
using namespace Components;
using namespace Math;
using namespace Video;

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
		Entity* yellowBlock1 = new Entity("Yellow Brick 1");
		yellowBlock1->AddComponent(new SpriteRenderer(yellowBlockTexture));
		yellowBlock1->SetTransform(Transform(Vector2D(0.2f, 0.2f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(yellowBlock1);

		// yellow block entity 2
		Entity* yellowBlock2 = new Entity("Yellow Brick 2");
		yellowBlock2->AddComponent(new SpriteRenderer(yellowBlockTexture));
		yellowBlock2->SetTransform(Transform(Vector2D(-0.2f, 0.2f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(yellowBlock2);

		//// blue block entity 2
		//Entity* blueBlock = new Entity("Blue Brick");
		//blueBlock->AddComponent(new SpriteRenderer(blueBlockTexture));
		//blueBlock->SetTransform(Transform(Vector2D(-0.0f, -0.2f), 0.0f, Vector2D(0.33f, 0.33f)));
		//this->AddEntity(blueBlock);
	}
}
