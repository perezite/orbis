#include "NewRectangleRenderer.h"

#include "../Video/VideoManager.h"
#include "../Core/TimeManager.h"
#include "../Game/Entity.h"
#include "../Game/Transform.h"
using namespace Core;
using namespace Game;
using namespace Video;

#include "../../Base/Math/MathHelper.h"
using namespace Math;

namespace Components
{
	const float NewRectangleRenderer::MIN_BLOCK_SCALE = 0.01f;
	const float NewRectangleRenderer::MAX_BLOCK_SCALE = 0.05f;

	NewRectangleRenderer::NewRectangleRenderer() : Renderer()
	{
		GetMaterial()->SetTexture(NULL);
		GetMaterial()->SetShader(Shader::GetFlatShader());
		SetMesh(Mesh::GetFlatQuad());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);

		m_isGrowing = rand() % 2 == 0 ? true : false;
	}

	void NewRectangleRenderer::Update()
	{
		float dt = TimeManager::GetInstance()->GetDeltaSeconds();
		Transform* trans = GetParent()->GetTransform();

		float deltaScale = m_isGrowing ? dt * 0.01f : dt * -0.01f;
		GetParent()->GetTransform()->scale += Vector2D(deltaScale, deltaScale);

		if (trans->scale.GetX() < MIN_BLOCK_SCALE)
			m_isGrowing = true;

		if (trans->scale.GetX() > MAX_BLOCK_SCALE)
			m_isGrowing = false;
	}
}
