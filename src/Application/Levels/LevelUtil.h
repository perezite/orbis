#pragma once

#include "../Controllers/LevelSwitchButtonController.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Game/Level.h"
using namespace orb::game;
using namespace controllers;
using namespace orb::video;
using namespace orb::components;


namespace levels
{
	class LevelUtil
	{
	public:
		template <class T>
		static void AddLevelSwitcher(Level* currentLevel, bool isForward)
		{
			VideoManager* video = VideoManager::getInstance();

			Camera* cam = Camera::getInstance();
			float horzPos = isForward ? 0.45f * cam->getSize().x : -0.45f * cam->getSize().x;
			Texture* tex = isForward ? video->getTexture("Textures/OverlayRight.png") : video->getTexture("Textures/OverlayLeft.png");

			Entity* nextLevel = new Entity(isForward ? "Next level Button" : "Previous level Button");
			nextLevel->addComponent(new SpriteRenderer(tex));
			nextLevel->addComponent(new LevelSwitchButtonController<T>(isForward));
			nextLevel->setTransform(Transform(Vector2D(horzPos, 0.45f * cam->getSize().y), 0.0f, Vector2D(0.1f, 0.1f), TransformSpace::Camera));
			currentLevel->addEntity(nextLevel);
		}
	};
}