#include "Vector2D.h"

#include "MathUtil.h"

#include "../System/StringUtil.h"
using namespace base;

#include <sstream>
#include <iostream>
#include <iomanip>
#include <math.h>

namespace base
{
	const Vector2D Vector2D::Zero = Vector2D(0.0f, 0.0f);

	const Vector2D Vector2D::One = Vector2D(1.0f, 1.0f);

	const Vector2D& Vector2D::operator=(const Vector2D &other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

	const Vector2D Vector2D::operator+(const Vector2D & other) const
	{
		return Vector2D(x + other.x, y + other.y);
	}

	const Vector2D Vector2D::operator-(const Vector2D &other) const
	{
		return Vector2D(x - other.x, y - other.y);
	}

	const Vector2D Vector2D::operator*(float scalar) const
	{
		return Vector2D(scalar * x, scalar * y);
	}

	const Vector2D Vector2D::operator-() const
	{
		return Vector2D(-x, -y);
	}

	const Vector2D Vector2D::operator+=(const Vector2D & other)
	{
		Vector2D result = *this + other;
		x = result.x; y = result.y;
		return *this + other;
	}

	const Vector2D Vector2D::normalized() const
	{
		return scaled(1.0f);
	}

	const Vector2D Vector2D::scaled(float length) const
	{
		Vector2D scaled((this->x * length) / this->getCount(), (this->y * length) / this->getCount());
		return scaled;
	}
}