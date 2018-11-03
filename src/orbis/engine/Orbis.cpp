#include "Orbis.h"

namespace orb
{
	Orbis* Orbis::instance()
	{
		static Orbis instance;
		return &instance;
	}

	void Orbis::updateFrame()
	{
		m_currentLevel->update();
	}

	Orbis::Orbis()
	{
		m_currentLevel = new Level();
	}
}

