#include "SimpleParticleRenderer.h"

#include "../Orbis.h"
using namespace orb::video;
using namespace orb::core;
using namespace orb::game;

#include "../../Base/Math/MathHelper.h"
#include "../../Base/System/MemoryHelper.h"
using namespace base::math;
using namespace base::system;

namespace orb
{
	namespace components
	{
		SimpleParticleRenderer::SimpleParticleRenderer(Texture * texture) : m_texture(texture)
		{ }

		SimpleParticleRenderer::~SimpleParticleRenderer()
		{
			MemoryHelper::clear(m_particles);
		}

		void SimpleParticleRenderer::start()
		{
			spawnParticle(Transform(Vector2D(-0.1f, -0.1f), 0.0f, Vector2D(0.1f, 0.1f)), Color(1.0f, 1.0f, 1.0f, 0.5f));
			spawnParticle(Transform(Vector2D(+0.1f, -0.1f), 0.0f, Vector2D(0.1f, 0.1f)), Color(1.0f, 1.0f, 1.0f, 1.0f));
		}

		void SimpleParticleRenderer::spawnParticle(const Transform& transform, const Color& color)
		{
			Particle* particle = new Particle(m_texture, color, transform, Vector2D::Zero);
			m_particles.push_back(particle);
		}
	}
}