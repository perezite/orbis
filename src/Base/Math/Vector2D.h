#pragma once

#include <string>
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
		static float distance(Vector2D point1, Vector2D point2) { return (point2 - point1).getCount(); }

		// deserialize from string 
		static Vector2D load(std::string json);

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
		float getCount() const { return sqrtf(x * x + y * y);  }

		// get normalized
		const Vector2D normalized() const;

		// get scaled
		const Vector2D scaled(float length) const;

		// serialize to string
		const std::string load(int precision = 5);

	public:
		// the x component 
		float x;

		// the y component
		float y;
	};
}