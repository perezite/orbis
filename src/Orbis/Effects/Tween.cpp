#include "Tween.h"

#include "../Core/AssetHelper.h"
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
			m_curve.FromString(json);
		}
	}
}
