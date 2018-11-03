#include "Level.h"

namespace orb 
{
	void Level::update()
	{
		for (unsigned int i = 0; i < m_entities.size(); i++)
			m_entities[i]->update();
	}
}
