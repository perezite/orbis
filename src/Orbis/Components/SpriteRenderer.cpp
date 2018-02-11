#include "SpriteRenderer.h"

#include "../Video/VideoManager.h"
#include "../Core/TimeManager.h"
using namespace Video;
using namespace Core;

namespace Components
{
	SpriteRenderer::SpriteRenderer(Texture* texture)
		: Component(), m_texture(texture)
	{}

	void SpriteRenderer::Start()
	{
		m_renderable.GetMaterial()->SetTexture(m_texture);
		m_renderable.GetMaterial()->SetShader(Shader::GetDiffuseShader());
		m_renderable.GetMaterial()->SetColor(Color::White);
		m_renderable.SetMesh(Mesh::GetTexturedQuad());
		m_renderable.SetTransform(GetParent()->GetTransform());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderable(&m_renderable);
	}

	void SpriteRenderer::SetTexture(Texture * texture)
	{
		m_renderable.GetMaterial()->SetTexture(texture);
		VideoManager::GetInstance()->GetRenderDevice()->UpdateRenderable(&m_renderable);
	}
}