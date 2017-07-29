#include "Entity.h"

namespace Game
{
	Entity::~Entity()
	{
		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			delete m_components[i];
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
		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->Start();
		}
	}

	void Entity::Update()
	{
		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->Update();
		}
	}

	void Entity::Render()
	{
		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->Render();
		}
	}
}

