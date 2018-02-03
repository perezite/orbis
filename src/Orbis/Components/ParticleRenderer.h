#pragma once

#include "Renderer.h"

#include "../Video/Texture.h"
#include "../Game/Transform.h"
#include "../Effects/Particle.h"
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
		ParticleRenderer(Texture* texture, float lifetime) : m_texture(texture), m_lifetime(lifetime) {}

		// override
		void Start();

		// override
		void Update();

		// override
		std::vector<Transform> GetRenderTransforms();

	private: 
		// the texture
		Texture* m_texture;

		// the particles current lifetimes in seconds
		std::vector<Particle> m_particles;

		// the particles of the particle system
		float m_lifetime;
	};
}