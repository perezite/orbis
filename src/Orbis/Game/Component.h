#pragma once

#include <stddef.h>

namespace Game
{
	class Entity;

	class Component
	{
	public:
		// default constructor
		Component() : m_parentEntity(NULL) { }

		// constructor
		Component(Entity* parentEntity) : m_parentEntity(parentEntity) { };

		// update
		virtual void Update() = 0;

		// render
		virtual void Render() = 0;

		// set entity
		void SetParentEntity(Entity* parentEntity) { m_parentEntity = parentEntity; }

		// get entity
		Entity *GetParentEntity() { return m_parentEntity; }

	private: 
		// entity which uses the component
		Entity *m_parentEntity;
	};
}