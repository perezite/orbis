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
		SetMesh(Mesh::GetTexturedQuad());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);
	}
}