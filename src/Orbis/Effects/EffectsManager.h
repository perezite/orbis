#pragma once

#include "Tween.h"

#include <string>

namespace Effects
{
	class EffectsManager
	{
	public: 
		// get instance
		static EffectsManager* getInstance();

		// clear the manager
		void clear();

		// get a tween
		Tween* GetTween(std::string assetPath);

	protected:
		// singleton constructor
		EffectsManager() {}

	private:
		// a list of tweens
		std::map<std::string, Tween*> m_tweens;
	};
}