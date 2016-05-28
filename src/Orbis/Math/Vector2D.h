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

		// constructor 
		Vector2D(const Vector2D &other) : m_x(other.m_x), m_y(other.m_y) { }

		// destructor
		virtual ~Vector2D() { };

		// assignment
		const Vector2D& operator=(const Vector2D &other);

		// addition
		const Vector2D operator+(const Vector2D &other) const;

		// subtraction
		const Vector2D operator-(const Vector2D &other) const;

		// additive inverse
		const Vector2D operator-() const;

		// get x
		float GetX() const { return m_x; }

		// get y
		float GetY() const { return m_y; }

		// set x
		void SetX(float x) { m_x = x; }

		// set y
		void SetY(float y) { m_y = y; }

	public:
		// zero vector
		static const Vector2D Zero;

		// one vector
		static const Vector2D One;

	private:
		float m_x;
		float m_y;
	};
}