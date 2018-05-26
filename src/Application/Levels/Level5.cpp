#include "Level5.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Video/TextureAtlas.h"
using namespace Components;
using namespace Video;

namespace Levels
{
	void Level5::Start()
	{
		// init textures
		Texture* yellowBlockTex = new Texture(this, "Textures/YellowBlock.png", true);
		Texture* redBlockTex = new Texture(this, "Textures/RedBlock.png", true);
		Texture* greenBlockTex = new Texture(this, "Textures/GreenBlock.png", true);

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

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
