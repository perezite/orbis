#include "Particle.h"

#include "../Video/VideoManager.h"
using namespace Video;

namespace Effects
{
	Particle::Particle(Texture * texture, const Transform & transform, const Vector2D & velocity) : m_renderable(NULL), m_transform(transform), m_velocity(velocity), m_lifetime(0.5f)
	{
		AddRenderable(texture);
	}

	Particle::~Particle()
	{
		// VideoManager::GetInstance()->GetRenderDevice()->DeleteRenderable(m_renderable);
		delete m_renderable;
	}

	void Particle::AddRenderable(Texture* texture)
	{
		m_renderable = new Renderable();
		m_renderable->GetMaterial()->SetTexture(texture);
		m_renderable->GetMaterial()->SetColor(Color(1.0f, 1.0f, 1.0f, 0.5f));
		m_renderable->GetMaterial()->SetShader(Shader::GetDiffuseShader());
		m_renderable->SetMesh(Mesh::GetTexturedQuad());
		m_renderable->SetTransform(&m_transform);
		// VideoManager::GetInstance()->GetRenderDevice()->AddRenderable(m_renderable);
	}
}