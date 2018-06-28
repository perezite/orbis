#include "EffectsManager.h"
#include "EffectsManager.h"

namespace orbis
{
	namespace effects
	{
		EffectsManager* EffectsManager::getInstance()
		{
			static EffectsManager instance;
			return &instance;
		}

		void EffectsManager::clear()
		{
			for (std::map<std::string, Tween*>::iterator it = m_tweens.begin(); it != m_tweens.end(); it++)
				delete (*it).second;
			m_tweens.clear();
		}

		Tween* EffectsManager::getTween(std::string assetPath)
		{
			if (m_tweens[assetPath])
				return m_tweens[assetPath];

			Tween* tween = new Tween(assetPath);
			m_tweens[assetPath] = tween;
			return tween;
		}
	}
}