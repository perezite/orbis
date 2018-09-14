#pragma once

#include "../Orbis.h"
using namespace orb::game;
using namespace orb::video;

#include "../../Base/Math/Range.h"
using namespace base::math;

namespace orb
{
	namespace effects
	{
		// a particle in a particle system. The values are currently hardcoded
		class Particle
		{
		public:
			// ctor
			Particle(Texture * texture, const Color& color, const Transform & transform, const Vector2D & velocity);

			// dtor
			virtual ~Particle();

			// get the transforms
			Transform* getTransform() { return &m_transform; }

			// get the current lifetime
			float getCurrentLifetime() const { return m_lifetime; }

			// set the current lifetime
			void setCurrentLifetime(float lifetime) { m_lifetime = lifetime; }

			// get the velocity
			const Vector2D& getVelocity() const { return m_velocity; }

		protected:
			// add a renderable
			void addRenderable(Texture* texture);

		private:
			// the renderable
			Renderable* m_renderable;

			// the transform
			Transform m_transform;

			// the velocity
			Vector2D m_velocity;

			// the current lifetime
			float m_lifetime;

			// the color 
			Color m_color;
		};
	}
}