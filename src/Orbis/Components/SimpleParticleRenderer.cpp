#include "SimpleParticleRenderer.h"

#include "TweenInspector.h"

#include "../Core/TimeManager.h"
#include "../Game/LevelManager.h"
using namespace Video;
using namespace Core;
using namespace Game;

#include "../../Base/Math/MathHelper.h"
#include "../../Base/System/MemoryHelper.h"
using namespace Math;
using namespace System;

namespace Components
{
	SimpleParticleRenderer::SimpleParticleRenderer(Texture * texture) : m_texture(texture)
	{ }

	SimpleParticleRenderer::~SimpleParticleRenderer()
	{
		MemoryHelper::Clear(m_particles);
	}

	void SimpleParticleRenderer::Start()
	{
		AddParticle(Transform(Vector2D(-0.1f, -0.1f), 0.0f, Vector2D(0.1f, 0.1f)), Color(1.0f, 1.0f, 1.0f, 0.5f));
		AddParticle(Transform(Vector2D(+0.1f, -0.1f), 0.0f, Vector2D(0.1f, 0.1f)), Color(1.0f, 1.0f, 1.0f, 1.0f));
	}

	void SimpleParticleRenderer::AddParticle(const Transform& transform, const Color& color)
	{
		Particle* particle = new Particle(m_texture, color, transform, Vector2D::Zero);
		m_particles.push_back(particle);
	}
}
