#include "ParticleRenderer.h"

#include "TweenInspector.h"

#include "../Core/TimeManager.h"
#include "../Game/LevelManager.h"
#include "../Effects/EffectsManager.h"
using namespace orbis::core;
using namespace orbis::game;
using namespace orbis::effects;

#include "../../Base/Math/MathHelper.h"
#include "../../Base/System/MemoryHelper.h"
using namespace base::math;
using namespace base::system;

namespace orbis
{
	namespace components
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
			Tween* alphaTween = EffectsManager::getInstance()->getTween("Tweens/GreenParticlesAlpha.tween");
			LevelManager::getInstance()->getCurrentLevel()->addEntity(TweenInspector::tryConstructEntity(m_parentLevel, alphaTween, KeyCode::b));
		}

		void ParticleRenderer::update()
		{
			updateParticles();

			cleanupParticles();

			emitParticles();

			m_lastEntityPos = getParent()->getTransform()->position;
		}

		void ParticleRenderer::updateParticles()
		{
			float dt = TimeManager::getInstance()->getDeltaSeconds();

			// update lifetime
			for (unsigned int i = 0; i < m_particles.size(); i++)
				m_particles[i]->setCurrentLifetime(m_particles[i]->getCurrentLifetime() - dt);

			// update position
			for (unsigned int i = 0; i < m_particles.size(); i++)
				m_particles[i]->getTransform()->position += m_particles[i]->getVelocity() * dt;
		}

		void ParticleRenderer::cleanupParticles()
		{
			// delete outdated particles
			for (unsigned int i = 0; i < m_particles.size();)
			{
				if (m_particles[i]->getCurrentLifetime() <= 0.0f)
					MemoryHelper::remove(m_particles, i);
				else
					i++;
			}
		}

		void ParticleRenderer::emitParticles()
		{
			float dt = TimeManager::getInstance()->getDeltaSeconds();
			float emissionPeriod = 1.0f / float(m_emissionRate);

			m_timeToNextEmission -= dt;
			if (m_timeToNextEmission < emissionPeriod)
			{
				spawnParticle();
				m_timeToNextEmission += emissionPeriod;
			}
		}

		void ParticleRenderer::spawnParticle()
		{
			float dt = TimeManager::getInstance()->getDeltaSeconds();
			Vector2D entityVelocity = (m_lastEntityPos - getParent()->getTransform()->position) * (1.0f / dt);

			Vector2D position = getParent()->getTransform()->position + MathHelper::getRandomOnUnitCircle() * m_emissionSphereShellRadius;
			Vector2D particleVelocity = (MathHelper::getRandomOnUnitCircle() * m_initialSpeed) + (entityVelocity * m_velocityInheritance);
			Transform transform(position, 0.0f, Vector2D(m_initialSize, m_initialSize));
			m_particles.push_back(new Particle(m_texture, Color::White, transform, particleVelocity));

		}
	}
}