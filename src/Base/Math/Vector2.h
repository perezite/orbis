#pragma once

#include <string>
#include <math.h>

namespace base
{
	// Represents a vector with two elements
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
		T length() const
		{
			return sqrt(x * x + y * y);
		}

		// get normalized
		const Vector2 normalized() const;

		// get scaled
		const Vector2 scaled(T newLength) const;

		// distance between two vectors
		static T distance(Vector2 left, Vector2 right)
		{
			Vector2 d = right - left;
			return sqrt(d.x * d.x + d.y * d.y);
		}

	public:
		// the x component 
		T x;

		// the y component
		T y;
	};

	template <class T>
	const Vector2<T> Vector2<T>::Zero = Vector2<T>(0, 0);

	template <class T>
	const Vector2<T> Vector2<T>::One = Vector2<T>(1, 1);

	template <class T>
	inline Vector2<T> operator*(const Vector2<T>& left, T right)
	{
		return Vector2<T>(left.x * right, left.y * right);
	}

	template <class T>
	inline Vector2<T> operator*(T left, const Vector2<T>& right)
	{
		return Vector2<T>(left * right.x, left * right.y);
	}

	template <class T>
	inline Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.x + right.x, left.y + right.y);
	}

	template <class T>
	inline Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.x - right.x, left.y - right.y);
	}

	template <class T>
	inline const Vector2<T>& Vector2<T>::operator=(const Vector2<T>& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	template <class T>
	inline const Vector2<T> Vector2<T>::operator-() const
	{
		return Vector2<T>(-x, -y);
	}

	template <class T>
	inline const Vector2<T> Vector2<T>::operator+=(const Vector2<T> & other)
	{
		Vector2<T> result = *this + other;
		x = result.x; y = result.y;
		return *this + other;
	}

	template <class T>
	inline const Vector2<T> Vector2<T>::normalized() const
	{
		return scaled(1);
	}

	template <class T>
	inline const Vector2<T> Vector2<T>::scaled(T newLength) const
	{
		Vector2<T> scaled((this->x * newLength) / length(), (this->y * newLength) / length());
		return scaled;
	}
	
	typedef Vector2<int>          Vector2i;
	typedef Vector2<unsigned int> Vector2u;
	typedef Vector2<float>        Vector2f;
}