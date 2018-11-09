#pragma once

#include "Transform.h"

namespace orb
{
	class Transformable
	{
	public:
		Transformable() { };

		const Transform& getTransform() { return m_transform; }

	private:
		Transform m_transform;
	};
}
