#pragma once

#include "../Game/Transform.h"
using namespace Game;

#include "../../Base/Math/Range.h"
using namespace Math;

namespace Effects
{
	// a particle in a particle system
	class Particle 
	{
	public:
		// ctor
		Particle(const Transform& transform, float initialLifetime) : m_transform(transform), m_lifetime(initialLifetime) {}

		// get the transforms
		const Transform& GetTransform() const { return m_transform; }

		// get the current lifetime
		float GetCurrentLifetime() const { return m_lifetime; }

		// set the current lifetime
		void SetCurrentLifetime(float lifetime) { m_lifetime = lifetime; }

	private:
		// the transform
		Transform m_transform;

		// the current lifetime
		float m_lifetime;

		// the initial size range
		Range<float> m_initialSize;
	};
}