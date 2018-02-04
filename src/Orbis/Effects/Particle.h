#pragma once

#include "../Game/Transform.h"
using namespace Game;

#include "../../Base/Math/Range.h"
using namespace Math;

namespace Effects
{
	// a particle in a particle system. The values are currently hardcoded
	class Particle 
	{
	public:
		// ctor
		Particle(const Transform& transform, const Vector2D& velocity) : m_transform(transform), m_velocity(velocity), m_lifetime(0.5f) {}

		// get the transforms
		Transform& GetTransform() { return m_transform; }

		// get the current lifetime
		float GetCurrentLifetime() const { return m_lifetime; }

		// set the current lifetime
		void SetCurrentLifetime(float lifetime) { m_lifetime = lifetime; }

		// get the velocity
		const Vector2D& GetVelocity() const { return m_velocity; }

	private:
		// the transform
		Transform m_transform;

		// the velocity
		Vector2D m_velocity;

		// the current lifetime
		float m_lifetime;
	};
}