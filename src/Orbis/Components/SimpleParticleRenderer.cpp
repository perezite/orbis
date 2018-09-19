#include "SimpleParticleRenderer.h"

#include "TweenInspector.h"

#include "../Core/TimeManager.h"
#include "../Game/LevelManager.h"

#include "../../Base/Math/MathUtil.h"
#include "../../Base/System/MemoryUtil.h"
using namespace base;

namespace orb
{
	SimpleParticleRenderer::SimpleParticleRenderer(Texture * texture) : m_texture(texture)
	{ }

	SimpleParticleRenderer::~SimpleParticleRenderer()
	{
		MemoryUtil::clear(m_particles);
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