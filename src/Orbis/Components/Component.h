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

		// start
		virtual void Start() { };

		// update
		virtual void Update() { };

		// render
		virtual void Render() { };

		// set entity
		void SetParent(Game::Entity* parent) { m_parent = parent; }

		// get entity
		Game::Entity *GetParent() { return m_parent; }

	private: 
		// entity which uses the component
		Game::Entity *m_parent;
	};
}