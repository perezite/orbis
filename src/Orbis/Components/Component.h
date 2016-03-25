#pragma once

#include <stddef.h>

namespace Game
{
	class Entity;
}

namespace Components
{
	class Component
	{
	public:
		// default constructor
		Component() : m_parent(NULL) { }

		// constructor
		Component(Game::Entity* parent) : m_parent(parent) { };

		// update
		virtual void Update() = 0;

		// render
		virtual void Render() = 0;

		// set entity
		void SetParent(Game::Entity* parent) { m_parent = parent; }

		// get entity
		Game::Entity *GetParent() { return m_parent; }

	private: 
		// entity which uses the component
		Game::Entity *m_parent;
	};
}