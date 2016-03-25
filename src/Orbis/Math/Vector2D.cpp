#include "Vector2D.h"

namespace Math
{
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
}