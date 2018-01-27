#include "Level6.h"

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Video/TextureAtlas.h"
using namespace Components;
using namespace Video;

namespace Levels
{
	Level6::Level6()
	{
		// init textures
		Texture* bleedingTestBlue = new Texture("Textures/BleedingTestBlue.png", true);
		Texture* bleedingTestGreen = new Texture("Textures/BleedingTestGreen.png", true);
		Texture* bleedingTestRed = new Texture("Textures/BleedingTestRed.png", true);
		Texture* bleedingTestYellow = new Texture("Textures/BleedingTestYellow.png", true);

		// init camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// init entities
		Entity* blueEntity = new Entity("Bleeding Test Blue");
		blueEntity->AddComponent(new SpriteRenderer(bleedingTestBlue));
		blueEntity->SetTransform(Transform(Vector2D(-0.25f, -0.25f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(blueEntity);

		Entity* greenEntity = new Entity("Bleeding Test Green");
		greenEntity->AddComponent(new SpriteRenderer(bleedingTestGreen));
		greenEntity->SetTransform(Transform(Vector2D(0.25f, -0.25f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(greenEntity);

		Entity* redEntity = new Entity("Bleeding Test Red");
		redEntity->AddComponent(new SpriteRenderer(bleedingTestRed));
		redEntity->SetTransform(Transform(Vector2D(0.25f, 0.25f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(redEntity);

		Entity* yellowEntity = new Entity("Bleeding Test Yellow");
		yellowEntity->AddComponent(new SpriteRenderer(bleedingTestYellow));
		yellowEntity->SetTransform(Transform(Vector2D(-0.25f, 0.25f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(yellowEntity);
	}
}