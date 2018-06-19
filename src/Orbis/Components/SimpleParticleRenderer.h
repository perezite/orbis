#pragma once

#include "Component.h"

#include "../Video/Texture.h"
#include "../Video/Renderable.h"
#include "../Game/Transform.h"
#include "../Effects/Particle.h"
#include "../Effects/Tween.h"
using namespace Video;
using namespace Game;
using namespace Effects;

#include <vector>

namespace Components
{
	// a renderer which renders a simplified particle system
	class SimpleParticleRenderer : public Component
	{
	public:
		// ctor
		SimpleParticleRenderer(Texture* texture);

		// dtor
		virtual ~SimpleParticleRenderer();

		// override
		void start();

	protected:
		// add a particle
		void spawnParticle(const Transform& transform, const Color& color);

	private: 
		// the texture
		Texture* m_texture;

		// the particles current lifetimes in seconds
		std::vector<Particle*> m_particles;
	};
}