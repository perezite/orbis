#include "ParticleRenderer.h"

#include "TweenInspector.h"

#include "../Video/VideoManager.h"
#include "../Core/TimeManager.h"
#include "../Game/LevelManager.h"
using namespace Video;
using namespace Core;
using namespace Game;

#include "../../Base/Math/MathHelper.h"
using namespace Math;

namespace Components
{
	ParticleRenderer::ParticleRenderer(Texture * texture)
		: m_texture(texture), m_lifetime(0.5), m_emissionSphereShellRadius(0.075f), m_emissionRate(40), m_timeToNextEmission(0.0f), m_initialSpeed(0.2f), m_initialSize(0.1f), m_velocityInheritance(0.25f)
	{
		m_currentColorAlpha = new Tween("Tweens/GreenParticlesAlpha.tween", 0.0f);
	}

	void ParticleRenderer::Start()
	{
		GetMaterial()->SetTexture(m_texture);
		GetMaterial()->SetColor(Color(1.0f, 1.0f, 1.0f, 0.5f));
		GetMaterial()->SetShader(Shader::GetDiffuseShader());
		SetMesh(Mesh::GetTexturedQuad());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);
		m_lastEntityPos = GetParent()->GetTransform()->position;
		GetParent()->GetTransform()->position = Vector2D(0.1f, 0.1f);

		// add an inspector for the alpha tween
		LevelManager::GetInstance()->GetCurrentLevel()->AddEntity(TweenInspector::TryConstructEntity(m_currentColorAlpha, KeyCode::b));
	}

	void ParticleRenderer::Update()
	{
		UpdateParticles();

		DeleteOutdatedParticles();

		EmitParticles();

		m_lastEntityPos = GetParent()->GetTransform()->position;
	}

	std::vector<Transform> ParticleRenderer::GetRenderTransforms()
	{
		std::vector<Transform> transforms;
		for (unsigned int i = 0; i < m_particles.size(); i++)
			transforms.push_back(m_particles[i].GetTransform());

		return transforms;
	}

	void ParticleRenderer::UpdateParticles()
	{
		float dt = TimeManager::GetInstance()->GetDeltaSeconds();

		// update lifetime
		for (unsigned int i = 0; i < m_particles.size(); i++)
			m_particles[i].SetCurrentLifetime(m_particles[i].GetCurrentLifetime() - dt);

		// update position
		for (unsigned int i = 0; i < m_particles.size(); i++)
			m_particles[i].GetTransform().position += m_particles[i].GetVelocity() * dt;
	}

	void ParticleRenderer::DeleteOutdatedParticles()
	{
		// delete outdated particles
		bool isDirty = false;
		for (std::vector<Particle>::iterator it = m_particles.begin(); it < m_particles.end(); )
		{
			if (it->GetCurrentLifetime() <= 0.0f)
				it = m_particles.erase(it);
			else
				it++;
		}

		// update the renderer
		if (isDirty)
			VideoManager::GetInstance()->GetRenderDevice()->UpdateRenderer(this);
	}

	void ParticleRenderer::EmitParticles()
	{
		float dt = TimeManager::GetInstance()->GetDeltaSeconds();
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
		float dt = TimeManager::GetInstance()->GetDeltaSeconds();
		Vector2D entityVelocity = (m_lastEntityPos - GetParent()->GetTransform()->position) * (1.0f/dt);

		Vector2D position = GetParent()->GetTransform()->position + MathHelper::GetRandomOnUnitCircle() * m_emissionSphereShellRadius;
		Vector2D particleVelocity = (MathHelper::GetRandomOnUnitCircle() * m_initialSpeed) + (entityVelocity * m_velocityInheritance);
		Transform transform(position, 0.0f, Vector2D(m_initialSize, m_initialSize));
		m_particles.push_back(Particle(transform, particleVelocity));
		VideoManager::GetInstance()->GetRenderDevice()->UpdateRenderer(this);
	}
}
