#include "LevelHelper.h"

#include "../Controllers/LevelSwitchButtonController.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Components/Camera.h"
using namespace Controllers;
using namespace Video;
using namespace Components;

namespace Levels
{
	void LevelHelper::AddLevelSwitcher(Level * currentLevel, Level * targetLevel, bool isForward)
	{
		VideoManager* video = VideoManager::GetInstance();

		Camera* cam = Camera::GetInstance();
		float horzPos = isForward ? 0.45f * cam->GetSize().x : -0.45f * cam->GetSize().x;
		Texture* tex = isForward ? video->GetTexture("Textures/OverlayRight.png") : video->GetTexture("Textures/OverlayLeft.png");

		Entity* nextLevel = new Entity(isForward ? "Next level Button" : "Previous level Button");
		nextLevel->AddComponent(new SpriteRenderer(tex));
		nextLevel->AddComponent(new LevelSwitchButtonController(targetLevel, isForward));
		nextLevel->SetTransform(Transform(Vector2D(horzPos, 0.45f * cam->GetSize().y), 0.0f, Vector2D(0.1f, 0.1f), TransformSpace::CameraSpace));
		currentLevel->AddEntity(nextLevel);
	}
}
