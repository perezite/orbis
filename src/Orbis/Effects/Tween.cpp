#include "Tween.h"

#include "../Core/AssetHelper.h"
#include "../Core/TimeManager.h"
using namespace Core;

#include "../../Base/System/StringHelper.h"
using namespace System;

#include <sstream>

namespace Effects
{
	void Tween::Save()
	{
		AssetHelper::SaveTextAsset(m_assetPath, m_curve.ToString());
	}

	void Tween::TryDeserialize()
	{
		std::string json;
		if (AssetHelper::TryLoadTextAsset(m_assetPath, json))
		{
			m_curve.Load(json);
		}
	}

	void Tween::Update(Vector2D* current)
	{
		m_elapsed += TimeManager::GetInstance()->GetDeltaSeconds();
		float x = m_elapsed / m_duration;

		if (x <= 1.0f)
		{
			float factor = m_curve.GetValue(x).y;

			*current = m_initial * factor;
		}
	}
}
