#pragma once

//#include "../Inspectors/Inspector.h"
//using namespace orb::inspectors;

#include <stddef.h>

namespace orb
{
	namespace game
	{
		class Entity;
	}

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

			// add an inspector
			// void SetInspector(orb::inspectors::Inspector* inspector) { m_inspector = inspector; };

		private:
			// entity which uses the component
			game::Entity *m_parent;

			// an inspector for this entity
			// orb::inspectors::Inspector *m_inspector;
		};
	}
}