#pragma once

#include <string>
#include <math.h>

namespace orb
{
	// a templataed vector with two elements
	template <class T>
	class Vector2
	{
	public:
		// zero vector
		static const Vector2 Zero;

		// one vector
		static const Vector2 One;


	public:
		// costructor 
		Vector2() : x(0), y(0) 
		{ }

		// constructor
		Vector2(T x_, T y_) : x(x_), y(y_) { }

		// constructor 
		Vector2(const Vector2 &other) : x(other.x), y(other.y) { }

		// destructor
		virtual ~Vector2() { };

		// assignment
		const Vector2& operator=(const Vector2& other);

		// additive inverse
		const Vector2 operator-() const;

		// inline addition 
		const Vector2 operator+=(const Vector2 &other);

		// get the length of a vector
		T length() const;

		// get normalized
		const Vector2 normalized() const;

		// get scaled
		const Vector2 scaled(T newLength) const;

		// distance between two vectors
		static T distance(Vector2 left, Vector2 right);

	public:
		// the x component 
		T x;

		// the y component
		T y;
	};

	#include "Vector2.inl"
	
	typedef Vector2<int>          Vector2i;
	typedef Vector2<unsigned int> Vector2u;
	typedef Vector2<float>        Vector2f;
}