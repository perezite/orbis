#pragma once

#include "..\..\Base\Math\Vector2D.h"
using namespace Math;

namespace Game
{
	// Represents the transformation of an Entity
	class Transform
	{
	public:
		// default constructor
		Transform() : m_position(Vector2D::Zero), m_rotation(0.0f), m_scale(Vector2D::One) { }

		// constructor
		Transform(Vector2D position, float rotation, Vector2D scale) { m_position = position; m_rotation = rotation; m_scale = scale; }

		// destructor
		virtual ~Transform() { }

		// get position
		Vector2D GetPosition() { return m_position; }

		// get rotation
		float GetRotation() { return m_rotation; }

		// get scale
		Vector2D GetScale() { return m_scale; }

		// set position 
		void SetPosition(Vector2D position) { m_position = position; }

		// set rotation
		void SetRotation(float rotation) { m_rotation = rotation;  }

		// set scale
		void SetScale(Vector2D scale) { m_scale = scale; }

	private:
		// position
		Vector2D m_position;

		// rotation
		float m_rotation;

		// scale
		Vector2D m_scale;
	};
}