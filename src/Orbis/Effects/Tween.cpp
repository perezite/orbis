#include "Tween.h"

#include "../Core/AssetHelper.h"
#include "../Core/TimeManager.h"
using namespace orbis::core;

#include "../../Base/System/StringHelper.h"
using namespace base::system;

#include <sstream>

namespace orbis
{
	namespace effects
	{
		Tween::Tween(std::string assetPath) :
			m_assetPath(assetPath), m_elapsed(0.0f)
		{
			if (AssetHelper::textAssetExists(m_assetPath))
			{
				std::string json = AssetHelper::loadTextAsset(m_assetPath);
				m_spline.loadFromJson(json);
			}
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
			AssetHelper::saveTextAsset(m_assetPath, m_spline.toJson());
		}
	}
}