#pragma once

#include "Transform.h"

#include "..\Components\Component.h"
using namespace Components;

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

		// set transform
		void SetTransform(Transform transform) { m_transform = transform; }

		// get transform
		Transform* GetTransform() { return &m_transform; }

		// add component
		void AddComponent(Component *component);

		// start the entity
		void Start();

		// update the entity
		void Update();

		// render the entity
		void Render();

	private: 
		// transform of the entity
		Transform m_transform;

		// components of the entity
		std::vector<Component*> m_components;
	};
}
