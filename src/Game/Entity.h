#pragma once

#include "Transformation.h"
#include "Component.h"

#include "..\Math\Vector2D.h"
using namespace Math;

#include <vector>

namespace Game
{

	// Represents an Entity in the game
	class Entity
	{
	public:
		// constructor
		Entity() { }

		// destructor
		virtual ~Entity();

		// set transformation
		void SetTransformation(Transformation transformation) { m_transformation = transformation; }

		// get transformation
		Transformation GetTransformation() { return m_transformation; }

		// add component
		void AddComponent(Component *component) { m_components.push_back(component); }

		// update the entity
		void Update();

		// render the entity
		void Render();

	private: 
		// the transformation of the entity
		Transformation m_transformation;

		//  components of the entity
		std::vector<Component*> m_components;
	};
}
