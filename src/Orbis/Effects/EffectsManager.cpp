#include "EffectsManager.h"
#include "EffectsManager.h"

namespace Effects
{
	EffectsManager* EffectsManager::GetInstance()
	{
		static EffectsManager instance;
		return &instance;
	}

	void EffectsManager::Clear()
	{
		for (std::map<std::string, Tween*>::iterator it = m_tweens.begin(); it != m_tweens.end(); it++)
			delete (*it).second;
		m_tweens.clear();
	}

	Tween* EffectsManager::GetTween(std::string assetPath)
	{
		if (m_tweens[assetPath])
			return m_tweens[assetPath];

		Tween* tween = new Tween(assetPath);
		m_tweens.insert(std::make_pair(assetPath, tween));
		return tween;
	}
}
