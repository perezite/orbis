#pragma once

#include "../../Orbis/Components/Component.h"
using namespace Components;

namespace Controllers
{
	class LevelSwitchButtonController : public Component
	{
	public:
		// ctor
		LevelSwitchButtonController(std::string targetLevelName, bool switchForward) : 
			Component(), m_targetLevelName(targetLevelName), m_switchForward(switchForward)
		{}

		// update
		void Update();

	private:
		// next level
		std::string m_targetLevelName;

		// is switching forward
		bool m_switchForward;
	};
}