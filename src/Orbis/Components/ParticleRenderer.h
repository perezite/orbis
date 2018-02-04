#pragma once

#include "Renderer.h"

#include "../Video/Texture.h"
#include "../Game/Transform.h"
#include "../Effects/Particle.h"
#include "../Effects/Tween.h"
using namespace Video;
using namespace Game;
using namespace Effects;

#include <vector>

namespace Components
{
	// a renderer which renders a particle system
	class ParticleRenderer : public Renderer
	{
	public:
		// ctor
		ParticleRenderer(Texture* texture);

		// override
		void Start();

		// override
		void Update();

		// override
		std::vector<Transform> GetRenderTransforms();

	protected:
		// update the particles
		void UpdateParticles();

		// delete outdated particles
		void DeleteOutdatedParticles();

		// emit new particles
		void EmitParticles();

		// add a particle
		void AddParticle();

	private: 
		// the texture
		Texture* m_texture;

		// the particles current lifetimes in seconds
		std::vector<Particle> m_particles;

		// the particles of the particle system
		float m_lifetime;

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

		// color alpha over lifetime
		Tween* m_currentColorAlpha;
	};
}