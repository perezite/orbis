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

	void Entity::AddComponent(Component *component)   		
	{
		component->SetParent(this);
		m_components.push_back(component);
	}

	void Entity::Start()
	{
		for each (Component *component in m_components)
		{
			component->Start();
		}
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

