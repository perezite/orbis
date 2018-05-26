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

namespace Levels
{
	void Level4::Start()
	{
		m_originalResolution = VideoManager::GetInstance()->GetResolution();
		VideoManager::GetInstance()->SetResolution(Vector2D(800, 800));

		// add camera
		Entity* cam = new Entity();
		cam->AddComponent(new Camera());
		AddEntity(cam);

		// add level switchers
		LevelHelper::AddLevelSwitcher(this, new Level3(), false);
		LevelHelper::AddLevelSwitcher(this, new Level5(), true);

		// add debug visualizer
		ORBIS_DEBUG (
			Entity* visualizer = new Entity();
			visualizer->AddComponent(new BinPackingVisualizer());
			AddEntity(visualizer);
		);
	}

	void Level4::Release()
	{
		VideoManager::GetInstance()->SetResolution(m_originalResolution);
	}
}
