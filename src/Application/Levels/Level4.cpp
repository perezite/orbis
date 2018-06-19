#include "Level4.h"

#include "Level3.h"
#include "Level5.h"
#include "LevelHelper.h"

#include "../Controllers/BinPackingVisualizer.h"
using namespace Controllers;

#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Core/DebugHelper.h"
using namespace Components;
using namespace Video;
using namespace Core;

#include <iostream>

namespace Levels
{
	void Level4::start()
	{
		m_originalResolution = VideoManager::getInstance()->getWindow()->getResolution();
		VideoManager::getInstance()->getWindow()->setResolution(Vector2D(800, 800));

		// add camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher<Level3>(this, false);
		LevelHelper::AddLevelSwitcher<Level5>(this, true);

		// add debug visualizer
		ORBIS_DEBUG (
			Entity* visualizer = new Entity();
			visualizer->AddComponent(new BinPackingVisualizer());
			AddEntity(visualizer);
		);
	}

	Level4::~Level4()
	{
		VideoManager::getInstance()->getWindow()->setResolution(m_originalResolution);
	}
}
