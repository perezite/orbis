#pragma once

namespace Game
{
	class Entity;

	class Component
	{
	public:
		// constructor
		Component(Entity* entity) : m_entity(entity) { };

		// update
		virtual void Update() = 0;

		// render
		virtual void Render() = 0;

		// get entity
		Entity *GetEntity() { return m_entity; }

	private: 
		// entity which uses the component
		Entity *m_entity;
	};
}