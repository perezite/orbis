#include "LevelHelper.h"

#include "../Controllers/LevelSwitchButtonController.h"
using namespace Controllers;

#include "../../Orbis/Components/Camera.h"
using namespace Components;

namespace Levels
{
	void LevelHelper::AddLevelSwitcher(Level * currentLevel, Level * targetLevel, bool isForward)
	{
		// create textures if needed
		if (!currentLevel->HasTexture("Textures/OverlayLeft.png"))
			new Texture(currentLevel, "Textures/OverlayLeft.png");
		if (!currentLevel->HasTexture("Textures/OverlayRight.png"))
			new Texture(currentLevel, "Textures/OverlayRight.png");

		Camera* cam = Camera::GetInstance();
		float horzPos = isForward ? 0.45f * cam->GetSize().x : -0.45f * cam->GetSize().x;
		Texture* tex = isForward ? currentLevel->GetTexture("Textures/OverlayRight.png") : currentLevel->GetTexture("Textures/OverlayLeft.png");

		Entity* nextLevel = new Entity(isForward ? "Next level Button" : "Previous level Button");
		nextLevel->AddComponent(new SpriteRenderer(tex));
		nextLevel->AddComponent(new LevelSwitchButtonController(targetLevel, isForward));
		nextLevel->SetTransform(Transform(Vector2D(horzPos, 0.45f * cam->GetSize().y), 0.0f, Vector2D(0.1f, 0.1f), TransformSpace::CameraSpace));
		currentLevel->AddEntity(nextLevel);
	}
}
