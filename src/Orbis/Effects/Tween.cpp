#include "Tween.h"

#include "../Core/AssetHelper.h"
#include "../Core/TimeManager.h"
using namespace Core;

#include "../../Base/System/StringHelper.h"
using namespace System;

#include <sstream>

namespace Effects
{
	Tween::Tween(std::string assetPath) :
	m_assetPath(assetPath), m_elapsed(0.0f)
	{
		if (AssetHelper::textAssetExists(m_assetPath))
		{
			std::string json = AssetHelper::loadTextAsset(m_assetPath);
			m_curve.loadFromJson(json);
		}
	}

	void Tween::saveToJsonFile()
	{
		AssetHelper::saveTextAsset(m_assetPath, m_curve.toJson());
	}

	void Tween::update(Vector2D* current, float duration)
	{
		m_elapsed += TimeManager::getInstance()->getDeltaSeconds();
		float x = m_elapsed / duration;

		if (x <= 1.0f)
		{
			float factor = m_curve.getValue(x).y;

			*current = m_initial * factor;
		}
	}
}
