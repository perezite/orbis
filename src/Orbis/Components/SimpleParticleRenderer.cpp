#include "SimpleParticleRenderer.h"

#include "TweenInspector.h"

#include "../Core/TimeManager.h"
#include "../Game/LevelManager.h"
using namespace Video;
using namespace Core;
using namespace Game;

#include "../../Base/Math/MathHelper.h"
using namespace Math;

namespace Components
{
	SimpleParticleRenderer::SimpleParticleRenderer(Texture * texture) : m_texture(texture)
	{ }

	SimpleParticleRenderer::~SimpleParticleRenderer()
	{
		for (unsigned int i = 0; i < m_particles.size(); i++)
			delete m_particles[i];
	}

	void SimpleParticleRenderer::Start()
	{
		AddParticle(Transform(Vector2D(-0.1f, -0.1f), 0.0f, Vector2D(0.1f, 0.1f)));
		AddParticle(Transform(Vector2D(+0.1f, -0.1f), 0.0f, Vector2D(0.1f, 0.1f)));
	}

	void SimpleParticleRenderer::AddParticle(const Transform& transform)
	{
		Particle* particle = new Particle(m_texture, transform, Vector2D::Zero);
		m_particles.push_back(particle);
	}
}
