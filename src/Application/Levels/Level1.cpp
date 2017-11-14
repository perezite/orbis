#include "Level1.h"

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
		camera->SetTransform(Transform(Vector2D(0.5f, 0.0f), MathHelper::GetPi() / 4.0f, Vector2D::One));
		this->AddEntity(camera);

		// sprite entity
		Entity* sprite = new Entity();
		sprite->AddComponent(new SpriteRenderer());
		// sprite->SetTransform(Transform(Vector2D(0.0f, 0.0f), 0.0f, Vector2D::One));
		// sprite->SetTransform(Transform(Vector2D(0.0f, 0.25f), 0.0f, Vector2D::One));
		this->AddEntity(sprite);
	}
}
