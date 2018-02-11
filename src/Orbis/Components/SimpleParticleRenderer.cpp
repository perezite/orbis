#include "SimpleParticleRenderer.h"

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
	SimpleParticleRenderer::SimpleParticleRenderer(Texture * texture) : m_texture(texture)
	{ }

	SimpleParticleRenderer::~SimpleParticleRenderer()
	{
		for (unsigned int i = 0; i < m_particles.size(); i++)
			delete m_particles[i];
		for (unsigned int i = 0; i < m_renderables.size(); i++)
			delete m_renderables[i];
	}

	void SimpleParticleRenderer::Start()
	{
		AddParticle(Transform(Vector2D(-0.1f, -0.1f), 0.0f, Vector2D(0.1f, 0.1f)));
		AddParticle(Transform(Vector2D(+0.1f, -0.1f), 0.0f, Vector2D(0.1f, 0.1f)));
	}

	void SimpleParticleRenderer::AddParticle(const Transform& transform)
	{
		Particle* particle = new Particle(transform, Vector2D::Zero);
		m_particles.push_back(particle);

		Renderable* renderable = new Renderable();
		renderable->GetMaterial()->SetTexture(m_texture);
		renderable->GetMaterial()->SetColor(Color(1.0f, 1.0f, 1.0f, 0.5f));
		renderable->GetMaterial()->SetShader(Shader::GetDiffuseShader());
		renderable->SetMesh(Mesh::GetTexturedQuad());
		renderable->SetTransform(particle->GetTransform());
		m_renderables.push_back(renderable);
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderable(renderable);
	}
}
