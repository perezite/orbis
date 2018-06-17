#pragma once

#include "Tween.h"

#include <string>

namespace Effects
{
	class EffectsManager
	{
	public: 
		// get instance
		static EffectsManager* GetInstance();

		// reset the manager
		void Reset();

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