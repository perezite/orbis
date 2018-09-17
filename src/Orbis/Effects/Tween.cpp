#include "Tween.h"

#include "../Core/AssetUtil.h"
#include "../Core/TimeManager.h"
#include "../Core/DebugUtil.h"
#include "../Game/LevelManager.h"
#include "../Components/TweenInspector.h"
using namespace orb::core;
using namespace orb::game;
using namespace orb::components;

#include "../../Base/System/StringUtil.h"
using namespace base::system;

#include <sstream>

namespace orb
{
	namespace effects
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

		void Tween::update(Vector2D* current, float duration)
		{
			m_elapsed += TimeManager::getInstance()->getDeltaSeconds();
			float x = m_elapsed / duration;

			if (x <= 1.0f)
			{
				float factor = m_spline.getValue(x).y;

				*current = m_initial * factor;
			}
		}

		void Tween::saveToJsonFile()
		{
			AssetUtil::saveTextAsset(m_assetPath, m_spline.toJson());
		}

		void Tween::createInspectorEntity()
		{	
			Level* level = LevelManager::getInstance()->getCurrentLevel();
			Entity* inspector = new Entity();
			inspector->addComponent(new TweenInspector(this));
			level->addEntity(inspector);
		}
	}
}