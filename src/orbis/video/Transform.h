#pragma once

#include "../math/Vector2.h"

namespace orb
{
	class Transform
	{
	public:
		static const Transform Identity;

		Transform(Vector2f position = Vector2f())
			: m_position(position)
		{ };

		Vector2f getPosition() const { return m_position; }

	private:
		Vector2f m_position;
	};

	Transform operator *(const Transform& left, const Transform& right);
}