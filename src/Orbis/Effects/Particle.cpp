#include "Particle.h"

#include "../Video/VideoManager.h"
using namespace Video;

namespace Effects
{
	Particle::Particle(Texture * texture, const Color& color, const Transform & transform, const Vector2D & velocity) 
		: m_renderable(NULL), m_transform(transform),  m_velocity(velocity), m_lifetime(0.5f), m_color(color)
	{
		AddRenderable(texture);
	}

	Particle::~Particle()
	{
		VideoManager::GetInstance()->GetRenderDevice()->DeleteRenderable(m_renderable);
		delete m_renderable;
	}

	void Particle::AddRenderable(Texture* texture)
	{
		m_renderable = new Renderable();
		m_renderable->GetMaterial()->SetTexture(texture);
		m_renderable->GetMaterial()->SetShader(Shader::GetDiffuseParticleShader());
		m_renderable->SetMesh(Mesh::CreateVertexColoredTexturedQuad(m_color));
		m_renderable->SetTransform(&m_transform);
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderable(m_renderable);
	}
}