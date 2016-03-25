#pragma once

#include "..\Math\Vector2D.h"
using namespace Math;

namespace Game
{
	// Represents the transformation of an Entity
	class Transformation
	{
	public:
		// default constructor
		Transformation() { } 

		// constructor
		Transformation(Vector2D position, float rotation) { m_position = position; m_rotation = rotation; }

		// destructor
		virtual ~Transformation() { }

		// get position
		Vector2D GetPosition() { return m_position; }

		// get rotation
		float GetRotation() { return m_rotation; }

		// set position 
		void SetPosition(Vector2D position) { m_position = position; }

		// set rotation
		void SetRotation(float rotation) { m_rotation = rotation;  }

	private:
		// position
		Vector2D m_position;

		// rotation
		float m_rotation;
	};
}