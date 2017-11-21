#include "Level1.h"

#include "../Controllers/CameraController.h"
#include "../Controllers/SpriteController.h"
using namespace Controllers;

#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/MathHelper.h"
using namespace Components;
using namespace Math;

namespace Levels
{
	Level1::Level1()
	{
		// camera entity
		Entity* camera = new Entity();
		camera->AddComponent(new Camera());
		camera->AddComponent(new CameraController());
		camera->SetTransform(Transform(Vector2D(0.3f, 0.0f), 0.0f, Vector2D::One));
		this->AddEntity(camera);

		// coordinate-system-sprite entity
		Entity* coordinateSystem = new Entity("CoordinateSystem");
		coordinateSystem->AddComponent(new SpriteRenderer("Textures/CoordinateSystem.png"));
		this->AddEntity(coordinateSystem);

		// sprite entity
		Entity* sprite = new Entity("Sprite");
		sprite->AddComponent(new SpriteController());
		sprite->AddComponent(new SpriteRenderer("Textures/TestTransparent.png"));
		sprite->SetTransform(Transform(Vector2D(0.25f, 0.1f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(sprite);
	}
}
