#pragma once

#include "../Controllers/LevelSwitchButtonController.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Game/Level.h"
using namespace Game;
using namespace Controllers;
using namespace Video;
using namespace Components;


namespace Levels
{
	class LevelHelper
	{
	public:
		template <class T>
		static void AddLevelSwitcher(Level* currentLevel, bool isForward)
		{
			VideoManager* video = VideoManager::getInstance();

			Camera* cam = Camera::getInstance();
			float horzPos = isForward ? 0.45f * cam->getCount().x : -0.45f * cam->getCount().x;
			Texture* tex = isForward ? video->getTexture("Textures/OverlayRight.png") : video->getTexture("Textures/OverlayLeft.png");

			Entity* nextLevel = new Entity(isForward ? "Next level Button" : "Previous level Button");
			nextLevel->AddComponent(new SpriteRenderer(tex));
			nextLevel->AddComponent(new LevelSwitchButtonController<T>(isForward));
			nextLevel->setTransform(Transform(Vector2D(horzPos, 0.45f * cam->getCount().y), 0.0f, Vector2D(0.1f, 0.1f), TransformSpace::Camera));
			currentLevel->AddEntity(nextLevel);
		}
	};
}