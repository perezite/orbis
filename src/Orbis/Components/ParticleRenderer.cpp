#include "ParticleRenderer.h"

#include "../Video/VideoManager.h"
#include "../Core/TimeManager.h"
using namespace Video;
using namespace Core;

namespace Components
{
	void ParticleRenderer::Start()
	{
		GetMaterial()->SetTexture(m_texture);
		GetMaterial()->SetShader(Shader::GetDiffuseShader());
		SetMesh(Mesh::GetTexturedQuad());
		m_particles.push_back(Particle(Transform(Vector2D(-0.2f, -0.2f), 0.0f, Vector2D(0.1f, 0.1f)), m_lifetime));
		m_particles.push_back(Particle(Transform(Vector2D(+0.2f, -0.2f), 0.0f, Vector2D(0.1f, 0.1f)), m_lifetime));
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);
		// VideoManager::GetInstance()->GetRenderDevice()->UpdateRenderer()
	}

	void ParticleRenderer::Update()
	{
		float dt = TimeManager::GetInstance()->GetDeltaSeconds();

		// update lifetime
		for (unsigned int i = 0; i < m_particles.size(); i++)
			m_particles[i].SetCurrentLifetime(m_particles[i].GetCurrentLifetime() - dt);

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

	std::vector<Transform> ParticleRenderer::GetRenderTransforms()
	{
		std::vector<Transform> transforms;
		for (unsigned int i = 0; i < m_particles.size(); i++)
		{
			transforms.push_back(m_particles[i].GetTransform());
		}

		return transforms;
	}
}
