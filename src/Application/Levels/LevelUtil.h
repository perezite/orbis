#pragma once

#include "../Controllers/LevelSwitchButtonController.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Game/Level.h"
using namespace orb;

namespace app
{
	class LevelUtil
	{
	public:
		template <class T>
		static void addLevelSwitcher(bool isForward)
		{
			Camera* cam = Camera::instance();
			float horzPos = isForward ? 0.45f * cam->getSize().x : -0.45f * cam->getSize().x;
			
			std::string tex = isForward ? "Textures/OverlayRight.png" : "Textures/OverlayLeft.png";
			
			LevelManager::instance()->getCurrentLevel()->build()->entity()
				->withComponent(new SpriteRenderer(tex))->withComponent(new LevelSwitchButtonController<T>(isForward))
				->withPosition(horzPos, 0.45f * cam->getSize().y)->withScale(0.1f, 0.1f)->withTransformSpace(TransformSpace::Camera)->go();
		}
	};
}