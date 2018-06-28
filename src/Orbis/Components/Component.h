#pragma once

#include <stddef.h>

namespace game
{
	class Entity;
}

namespace orbis
{
	namespace components
	{
		class Component
		{
		public:
			// default ctor
			Component() : m_parent(NULL) { }

			// ctor
			Component(game::Entity* parent) : m_parent(parent) { };

			// dtor
			virtual ~Component() { };

			// start
			virtual void start() { };

			// update
			virtual void update() { };

			// render
			virtual void renderDebug() { };

			// set entity
			void setParent(game::Entity* parent) { m_parent = parent; }

			// get entity
			game::Entity *getParent() { return m_parent; }

		private:
			// entity which uses the component
			game::Entity *m_parent;
		};
	}
}