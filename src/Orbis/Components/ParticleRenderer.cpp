#include "ParticleRenderer.h"

#include "../Video/VideoManager.h"
#include "../Core/TimeManager.h"
using namespace Video;
using namespace Core;

#include "../../Base/Math/MathHelper.h"
using namespace Math;

namespace Components
{
	ParticleRenderer::ParticleRenderer(Texture * texture)
		: m_texture(texture), m_lifetime(0.5), m_emissionSphereShellRadius(0.1f), m_emissionRate(40), m_timeToNextEmission(0.0f), m_initialSpeed(2.0f), m_initialSize(0.1f)
	{}

	void ParticleRenderer::Start()
	{
		GetMaterial()->SetTexture(m_texture);
		GetMaterial()->SetShader(Shader::GetDiffuseShader());
		SetMesh(Mesh::GetTexturedQuad());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);
	}

	void ParticleRenderer::Update()
	{
		UpdateParticles();

		DeleteOutdatedParticles();

		EmitParticles();
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

		for (unsigned int i = 0; i < m_particles.size(); i++)
			m_particles[i].SetCurrentLifetime(m_particles[i].GetCurrentLifetime() - dt);
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
		Vector2D position = GetParent()->GetTransform()->position + MathHelper::GetRandomOnUnitCircle() * m_emissionSphereShellRadius;
		Vector2D velocity = MathHelper::GetRandomOnUnitCircle() * m_initialSpeed;
		Transform transform(position, 0.0f, Vector2D(m_initialSize, m_initialSize));
		m_particles.push_back(Particle(transform, velocity));
		VideoManager::GetInstance()->GetRenderDevice()->UpdateRenderer(this);
	}
}
