#pragma once

namespace Math
{
	// Represents a 2D vector
	class Vector2D
	{
	public:
		// costructor 
		Vector2D() { m_x = 0.0f, m_y = 0.0f; }

		// constructor
		Vector2D (float x, float y) : m_x(x), m_y(y) { }

		// destructor
		virtual ~Vector2D() { };

		// get x
		float GetX() const { return m_x; }

		// get y
		float GetY() const { return m_y; }

		// set x
		void SetX(float x) { m_x = x; }

		// set y
		void SetY(float y) { m_y = y; }

	private:
		float m_x;
		float m_y;
	};
}