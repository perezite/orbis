#include "Vector2D.h"

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

	const Vector2D Vector2D::operator+(const Vector2D & other) const
	{
		return Vector2D(m_x + other.m_x, m_y + other.m_y);
	}

	const Vector2D Vector2D::operator-(const Vector2D &other) const
	{
		return Vector2D(m_x - other.m_x, m_y - other.m_y);
	}
	const Vector2D Vector2D::operator-() const
	{
		return Vector2D(-m_x, -m_y);
	}
}