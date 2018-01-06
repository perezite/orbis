#pragma once

#include <math.h>

namespace Math
{
	// Represents a 2D vector
	struct Vector2D
	{
	public:
		// zero vector
		static const Vector2D Zero;

		// one vector
		static const Vector2D One;

	public:
		// get distance between to points
		static float Distance(Vector2D point1, Vector2D point2) { return (point2 - point1).GetLength(); }

	public:
		// costructor 
		Vector2D() { x = 0.0f, y = 0.0f; }

		// constructor
		Vector2D (float x_, float y_) : x(x_), y(y_) { }

		// constructor 
		Vector2D(const Vector2D &other) : x(other.x), y(other.y) { }

		// destructor
		virtual ~Vector2D() { };

		// assignment
		const Vector2D& operator=(const Vector2D &other);

		// addition
		const Vector2D operator+(const Vector2D &other) const;

		// subtraction
		const Vector2D operator-(const Vector2D &other) const;

		// scalar multiplication
		const Vector2D operator*(float scalar) const;

		// additive inverse
		const Vector2D operator-() const;

		// inline addition 
		const Vector2D operator+=(const Vector2D &other);

		// get length
		float GetLength() const { return sqrtf(x * x + y * y);  }

	public:
		// the x component 
		float x;

		// the y component
		float y;
	};
}