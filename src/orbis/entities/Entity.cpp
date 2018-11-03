#include "Entity.h"
#include "../engine/Orbis.h"

#include <iostream>

namespace orb
{
	Entity::Entity()
	{
		Orbis::instance()->getCurrentLevel()->addEntity(this);
	}

	void Entity::update()
	{
		for (unsigned int i = 0; i < m_components.size(); i++)
			m_components[i]->update();
	}
}
