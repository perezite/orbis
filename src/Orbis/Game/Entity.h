#pragma once

#include "Transform.h"

#include "../Components/Component.h"

#include "../../Base/Base.h"
using namespace base;

#include <vector>
#include <string>

namespace orb
{
	// Represents an Entity in the game
	class Entity
	{
	public:
		// constructor
		Entity(std::string name = "") { m_name = name; }

		// destructor
		virtual ~Entity();

		// set transform
		void setTransform(Transform transform) { m_transform = transform; }

		// get transform
		Transform* getTransform() { return &m_transform; }

		// get the name
		std::string getName() const { return m_name; }

		// get components
		const std::vector<Component*>& getComponents() const { return m_components; }

		// get a component of a specific type
		template <class T> T* getComponent() 
		{
			for (unsigned int i = 0; i < m_components.size(); i++)
			{
				T* result = dynamic_cast<T*>(m_components[i]);
				if (result != NULL)
					return result;
			}

			return NULL;
		}

		// add component
		void addComponent(Component *component);

		// start the entity
		void start();

		// updateLevel the entity
		void update();

		// debug-render the entity
		void renderDebug();

	private:
		// transform of the entity
		Transform m_transform;

		// components of the entity
		std::vector<Component*> m_components;

		// name of the entity
		std::string m_name;
	};
}