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
		if (!EnvironmentUtil::isMobile()) {
			m_originalResolution = VideoManager::instance()->getWindow()->getResolution();
			VideoManager::instance()->getWindow()->setResolution(Vector2u(800, 800));
		}

		build()->entity()->withComponent(new Camera())->go();

		LevelUtil::addLevelSwitcher<Level3>(false);
		LevelUtil::addLevelSwitcher<Level5>(true);

		// add debug visualizer
		ORBIS_DEBUG(
			build()->entity()->withComponent(new BinPackingVisualizer())->go();
		)
	}

	Level4::~Level4()
	{
		if (!EnvironmentUtil::isMobile())
			VideoManager::instance()->getWindow()->setResolution(m_originalResolution);
	}
}
