#pragma once

#include "Tween.h"

#include <string>
#include <map>

namespace orb
{
	class EffectsManager
	{
	public:
		// get instance
		static EffectsManager* instance();

		// clear the manager
		void clear();

		// get a tween
		Tween* getTween(std::string assetPath);

	protected:
		// singleton constructor
		EffectsManager() {}

	private:
		// a list of tweens
		std::map<std::string, Tween*> m_tweens;
	};
}