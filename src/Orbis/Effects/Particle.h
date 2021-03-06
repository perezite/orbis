#pragma once

#include "../Game/Transform.h"
#include "../Video/Renderable.h"
#include "../Video/Color.h"

#include "../../Base/Base.h"
using namespace base;

namespace orb
{
	// a particle in a particle system. The values are currently hardcoded
	class Particle
	{
	public:
		// ctor
		Particle(Texture * texture, const Color& color, const Transform & transform, const Vector2f & velocity);

		// dtor
		virtual ~Particle();

		// get the transforms
		Transform* getTransform() { return &m_transform; }

		// get the current lifetime
		float getCurrentLifetime() const { return m_lifetime; }

		// set the current lifetime
		void setCurrentLifetime(float lifetime) { m_lifetime = lifetime; }

		// get the velocity
		const Vector2f& getVelocity() const { return m_velocity; }

	protected:
		// add a renderable
		void addRenderable(Texture* texture);

	private:
		// the renderable
		Renderable* m_renderable;

		// the transform
		Transform m_transform;

		// the velocity
		Vector2f m_velocity;

		// the current lifetime
		float m_lifetime;

		// the color 
		Color m_color;
	};
}