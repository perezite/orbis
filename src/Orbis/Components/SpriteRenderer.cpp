#include "SpriteRenderer.h"

#include "../Video/VideoManager.h"
#include "../Core/TimeManager.h"
using namespace Video;
using namespace Core;

namespace Components
{
	SpriteRenderer::SpriteRenderer(Texture* texture)
		: Renderer(), m_texture(texture)
	{}

	void SpriteRenderer::Start()
	{
		GetMaterial()->SetTexture(m_texture);
		GetMaterial()->SetShader(Shader::GetDiffuseShader());
		GetMaterial()->SetColor(Color::White);
		SetMesh(Mesh::GetTexturedQuad());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);
	}

	void SpriteRenderer::SetTexture(Texture * texture)
	{
		GetMaterial()->SetTexture(texture);
		VideoManager::GetInstance()->GetRenderDevice()->UpdateRenderer(this);
	}
}