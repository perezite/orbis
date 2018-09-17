#pragma once

#include "Component.h"

#include "../Video/Texture.h"
#include "../Video/Renderable.h"
#include "../Game/Transform.h"
#include "../Effects/Particle.h"
#include "../Game/Level.h"
using namespace orb::video;
using namespace orb::game;
using namespace orb::effects;

#include <vector>

namespace orb
{
	namespace components
	{
		// a renderer which renders a particle system
		class ParticleRenderer : public Component
		{
		public:
			// ctor
			ParticleRenderer(Texture* texture);

			// dtor
			virtual ~ParticleRenderer();

			// override
			void start() { };

			// override
			void update();

		protected:
			// update the particles
			void updateParticles();

			// delete outdated particles
			void cleanupParticles();

			// emit new particles
			void emitParticles();

			// add a particle
			void spawnParticle();

		private:
			// the texture
			Texture* m_texture;

			// the particles current lifetimes in seconds
			std::vector<Particle*> m_particles;

			// emission sphere shell radius
			float m_emissionSphereShellRadius;

			// emission rate in particles per second
			unsigned int m_emissionRate;

			// time to next particle emission in second
			float m_timeToNextEmission;

			// the initial speed of the particles
			float m_initialSpeed;

			// the initial size of the partices
			float m_initialSize;

			// amount of velocity inheritance
			float m_velocityInheritance;

			// the last position of the entity transforms
			Vector2D m_lastEntityPos;
		};
	}
}