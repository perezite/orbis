#pragma once

#include <stddef.h>

namespace orb
{

	class Entity;

	class Component
	{
	public:
		// default ctor
		Component() : m_parent(NULL) { }

		// ctor
		Component(Entity* parent) : m_parent(parent) { };

		// dtor
		virtual ~Component() { };

		// start
		virtual void start() { };

		// updateLevel
		virtual void update() { };

		// render
		virtual void renderDebug() { };

		// set entity
		void setParent(Entity* parent) { m_parent = parent; }

		// get entity
		Entity *getParent() { return m_parent; }

	private:
		// entity which uses the component
		Entity *m_parent;
	};
}