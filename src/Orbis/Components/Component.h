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
		virtual void Update() { };

		// render
		virtual void RenderDebug() { };

		// set entity
		void SetParent(Game::Entity* parent) { m_parent = parent; }

		// get entity
		Game::Entity *GetParent() { return m_parent; }

	private: 
		// entity which uses the component
		Game::Entity *m_parent;
	};
}