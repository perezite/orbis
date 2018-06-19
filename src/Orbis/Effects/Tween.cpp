#include "Tween.h"

#include "../Core/AssetHelper.h"
#include "../Core/TimeManager.h"
using namespace Core;

#include "../../Base/System/StringHelper.h"
using namespace System;

#include <sstream>

namespace Effects
{
	void Tween::save()
	{
		AssetHelper::saveTextAsset(m_assetPath, m_curve.toString());
	}

	void Tween::tryDeserialize()
	{
		std::string json;
		if (AssetHelper::tryLoadTextAsset(m_assetPath, json))
		{
			m_curve.load(json);
		}
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
