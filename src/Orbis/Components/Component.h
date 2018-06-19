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
		// default ctor
		Component() : m_parent(NULL) { }

		// ctor
		Component(Game::Entity* parent) : m_parent(parent) { };

		// dtor
		virtual ~Component() { };

		// start
		virtual void start() { };

		// update
		virtual void update() { };

		// render
		virtual void renderDebug() { };

		// set entity
		void setParent(Game::Entity* parent) { m_parent = parent; }

		// get entity
		Game::Entity *getParent() { return m_parent; }

	private: 
		// entity which uses the component
		Game::Entity *m_parent;
	};
}