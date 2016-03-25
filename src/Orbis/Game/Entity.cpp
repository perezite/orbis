#include "Entity.h"
#include "Entity.h"

namespace Game
{
	Entity::~Entity()
	{
		for each (Component *component in m_components)
		{
			delete component;
		}

		m_components.clear();
	}

	void Entity::Update()
	{
		for each (Component *component in m_components)
		{
			component->Update();
		}
	}

	void Entity::Render()
	{
		for each (Component *component in m_components)
		{
			component->Render();
		}
	}
}

