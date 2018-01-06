#include "Vector2D.h"

#include "MathHelper.h"

#include <math.h>

namespace Math
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

	const Vector2D Vector2D::Normalized() const
	{
		Vector2D normalized(this->x / this->GetLength(), this->y / this->GetLength());
		return normalized;
	}
}