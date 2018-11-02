#include "Vector2.h"

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

template<class T>
inline T Vector2<T>::length() const
{
	return sqrt(x * x + y * y);
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

template <class T>
inline T Vector2<T>::distance(Vector2<T> left, Vector2<T> right)
{
	Vector2<T> d = right - left;
	return sqrt(d.x * d.x + d.y * d.y);
}


