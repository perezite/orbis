#include "SpriteRenderer.h"

#include "../Video/VideoManager.h"
#include "../Core/TimeManager.h"
using namespace Video;
using namespace Core;

namespace Components
{
	const float SpriteRenderer::MIN_SCALE = 0.01f;
	const float SpriteRenderer::MAX_SCALE = 0.05f;

	SpriteRenderer::SpriteRenderer(Texture* texture)
		: Renderer(), m_texture(texture)
	{}

	void SpriteRenderer::Start()
	{
		GetMaterial()->SetTexture(m_texture);
		GetMaterial()->SetShader(Shader::GetDiffuseShader());
		SetMesh(Mesh::GetTexturedQuad());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);

		m_isGrowing = rand() % 2 == 0 ? true : false;
	}

	void SpriteRenderer::Update()
	{
		float dt = TimeManager::GetInstance()->GetDeltaSeconds();
		Transform* trans = GetParent()->GetTransform();

		float deltaScale = m_isGrowing ? dt * 0.01f : dt * -0.01f;
		GetParent()->GetTransform()->scale += Vector2D(deltaScale, deltaScale);

		if (trans->scale.GetX() < MIN_SCALE)
			m_isGrowing = true;

		if (trans->scale.GetX() > MAX_SCALE)
			m_isGrowing = false;
	}
}