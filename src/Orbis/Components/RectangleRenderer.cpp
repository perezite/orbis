#include "RectangleRenderer.h"

#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"
using namespace Core;
using namespace Video;

namespace Components
{
	const float RectangleRenderer::MIN_SCALE = 0.01f;
	const float RectangleRenderer::MAX_SCALE = 0.05f;

	void RectangleRenderer::Start()
	{
		GetMaterial()->SetTexture(NULL);
		GetMaterial()->SetShader(Shader::GetFlatShader());
		GetMaterial()->SetColor(m_color);
		SetMesh(Mesh::GetFlatQuad());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);

		m_isGrowing = rand() % 2 == 0 ? true : false;
	}

	void RectangleRenderer::Update()
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