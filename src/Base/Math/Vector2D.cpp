#include "Vector2D.h"

#include "MathHelper.h"

#include <math.h>

namespace Math
{
	const Vector2D Vector2D::Zero = Vector2D(0.0f, 0.0f);

	const Vector2D Vector2D::One = Vector2D(1.0f, 1.0f);

	const Vector2D& Vector2D::operator=(const Vector2D &other)
	{
		m_x = other.m_x;
		m_y = other.m_y;
		return *this;
	}

	const Vector2D Vector2D::Rotated(float alphaDegrees) const
	{
		float alpha = MathHelper::DegreesToRadian(alphaDegrees);
		float x = cosf(alpha)*GetX() - sinf(alpha)*GetY();
		float y = sinf(alpha)*GetX() + cosf(alpha)*GetY();
		return Vector2D(x, y);
	}

	const Vector2D Vector2D::operator+(const Vector2D & other) const
	{
		return Vector2D(m_x + other.m_x, m_y + other.m_y);
	}

	const Vector2D Vector2D::operator-(const Vector2D &other) const
	{
		return Vector2D(m_x - other.m_x, m_y - other.m_y);
	}

	const Vector2D Vector2D::operator*(float scalar) const
	{
		return Vector2D(scalar * m_x, scalar * m_y);
	}

	const Vector2D Vector2D::operator-() const
	{
		return Vector2D(-m_x, -m_y);
	}
}