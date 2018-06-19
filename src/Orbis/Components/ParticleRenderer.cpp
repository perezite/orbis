#include "ParticleRenderer.h"

#include "TweenInspector.h"

#include "../Core/TimeManager.h"
#include "../Game/LevelManager.h"
#include "../Effects/EffectsManager.h"
using namespace Core;
using namespace Game;
using namespace Effects;

#include "../../Base/Math/MathHelper.h"
#include "../../Base/System/MemoryHelper.h"
using namespace Math;
using namespace System;

namespace Components
{
	ParticleRenderer::ParticleRenderer(Level* parentLevel, Texture * texture) : 
		m_texture(texture), m_emissionSphereShellRadius(0.075f), m_emissionRate(40), m_timeToNextEmission(0.0f), 
		m_initialSpeed(0.2f), m_initialSize(0.1f), m_velocityInheritance(0.25f), m_parentLevel(parentLevel)
	{
	}

	ParticleRenderer::~ParticleRenderer()
	{
		MemoryHelper::clear(m_particles);
	}

	void ParticleRenderer::start()
	{
		Tween* alphaTween = EffectsManager::getInstance()->GetTween("Tweens/GreenParticlesAlpha.tween");
		LevelManager::getInstance()->GetCurrentLevel()->AddEntity(TweenInspector::TryConstructEntity(m_parentLevel, alphaTween, KeyCode::b));
	}

	void ParticleRenderer::Update()
	{
		UpdateParticles();

		CleanupParticles();

		EmitParticles();

		m_lastEntityPos = GetParent()->getTransform()->position;
	}

	void ParticleRenderer::UpdateParticles()
	{
		float dt = TimeManager::getInstance()->GetDeltaSeconds();

		// update lifetime
		for (unsigned int i = 0; i < m_particles.size(); i++)
			m_particles[i]->SetCurrentLifetime(m_particles[i]->GetCurrentLifetime() - dt);

		// update position
		for (unsigned int i = 0; i < m_particles.size(); i++)
			m_particles[i]->getTransform()->position += m_particles[i]->GetVelocity() * dt;
	}

	void ParticleRenderer::CleanupParticles()
	{
		// delete outdated particles
		for (unsigned int i = 0; i < m_particles.size();)
		{
			if (m_particles[i]->GetCurrentLifetime() <= 0.0f)
				MemoryHelper::Remove(m_particles, i);
			else
				i++;
		}
	}

	void ParticleRenderer::EmitParticles()
	{
		float dt = TimeManager::getInstance()->GetDeltaSeconds();
		float emissionPeriod = 1.0f / float(m_emissionRate);

		m_timeToNextEmission -= dt;
		if (m_timeToNextEmission < emissionPeriod)
		{
			AddParticle();
			m_timeToNextEmission += emissionPeriod;
		}
	}

	void ParticleRenderer::AddParticle()
	{
		float dt = TimeManager::getInstance()->GetDeltaSeconds();
		Vector2D entityVelocity = (m_lastEntityPos - GetParent()->getTransform()->position) * (1.0f/dt);

		Vector2D position = GetParent()->getTransform()->position + MathHelper::GetRandomOnUnitCircle() * m_emissionSphereShellRadius;
		Vector2D particleVelocity = (MathHelper::GetRandomOnUnitCircle() * m_initialSpeed) + (entityVelocity * m_velocityInheritance);
		Transform transform(position, 0.0f, Vector2D(m_initialSize, m_initialSize));
		m_particles.push_back(new Particle(m_texture, Color::White, transform, particleVelocity));

	}
}
