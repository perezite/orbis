#include "Entity.h"

#include "../../Base/System/MemoryHelper.h"
using namespace System;

namespace Game
{
	Entity::~Entity()
	{
		MemoryHelper::Clear(m_components);
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

	void Entity::RenderDebug()
	{
		for (unsigned int i = 0; i < m_components.size(); i++)
		{
			m_components[i]->RenderDebug();
		}
	}
}

