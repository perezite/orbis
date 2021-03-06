#include "Tween.h"

#include "../Core/AssetUtil.h"
#include "../Core/TimeManager.h"
#include "../Core/DebugUtil.h"
#include "../Game/LevelManager.h"
#include "../Components/TweenInspector.h"

#include "../../Base/Base.h"
using namespace base;

#include <sstream>
#include <algorithm>

namespace orb
{
	Tween::Tween(std::string assetPath) :
		m_assetPath(assetPath), m_elapsed(0.0f)
	{
		if (AssetUtil::textAssetExists(m_assetPath))
		{
			std::string json = AssetUtil::loadTextAsset(m_assetPath);
			m_spline.loadFromJson(json);
		}

		ORBIS_DEBUG(
			createInspectorEntity();
		);
	}

	float Tween::getValue(float duration)
	{
		m_elapsed += TimeManager::instance()->getDeltaSeconds();
		float t = std::min(m_elapsed / duration, 1.0f);
		float value = m_spline.getValue(t).y;

		return value;
	}

	void Tween::saveToJsonFile()
	{
		AssetUtil::saveTextAsset(m_assetPath, m_spline.toJson());
	}

	void Tween::createInspectorEntity()
	{	
		Level* level = LevelManager::instance()->getCurrentLevel();
		Entity* inspector = new Entity();
		inspector->addComponent(new TweenInspector(this));
		level->addEntity(inspector);
	}
}