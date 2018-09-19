#include "Level4.h"

#include "Level3.h"
#include "Level5.h"
#include "LevelUtil.h"

#include "../Controllers/BinPackingVisualizer.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

#include <iostream>

namespace app
{
	void Level4::start()
	{
		m_originalResolution = VideoManager::getInstance()->getWindow()->getResolution();
		VideoManager::getInstance()->getWindow()->setResolution(Vector2D(800, 800));

		// add camera
		Entity* cam = new Entity();
		cam->addComponent(new Camera());
		addEntity(cam);

		// add level switchers
		LevelUtil::AddLevelSwitcher<Level3>(this, false);
		LevelUtil::AddLevelSwitcher<Level5>(this, true);

		// add debug visualizer
		ORBIS_DEBUG (
			Entity* visualizer = new Entity();
			visualizer->addComponent(new BinPackingVisualizer());
			addEntity(visualizer);
		);
	}

	Level4::~Level4()
	{
		VideoManager::getInstance()->getWindow()->setResolution(m_originalResolution);
	}
}
