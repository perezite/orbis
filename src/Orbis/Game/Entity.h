#pragma once

#include "Transform.h"

#include "../Components/Component.h"
using namespace Components;

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include <vector>
#include <string>

namespace Game
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

		// add component
		void addComponent(Component *component);

		// start the entity
		void start();

		// update the entity
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
