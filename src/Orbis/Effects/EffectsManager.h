#pragma once

#include "../Orbis.h"

#include <string>

namespace orb
{
	namespace effects
	{
		class EffectsManager
		{
		public:
			// get instance
			static EffectsManager* getInstance();

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
}