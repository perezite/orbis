#include "Entity.h"

#include "../../Base/Base.h"
using namespace base;

namespace orb
{
	Entity::~Entity()
	{
		MemoryUtil::clear(m_components);
	}

	void Entity::addComponent(Component *component)
	{
		component->setParent(this);
		m_components.push_back(component);
	}

	void Entity::start()
	{
		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->start();
		}
	}

	void Entity::update()
	{
		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->update();
		}
	}

	void Entity::renderDebug()
	{
		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->renderDebug();
		}
	}
}