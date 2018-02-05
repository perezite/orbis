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
	class SimpleParticleRenderer : public Renderer
	{
	public:
		// ctor
		SimpleParticleRenderer(Texture* texture);

		// override
		void Start();

		// override
		std::vector<Transform> GetRenderTransforms();

	private: 
		// the texture
		Texture* m_texture;

		// the particles current lifetimes in seconds
		std::vector<Particle> m_particles;
	};
}