#include "RectangleRenderer.h"

#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"
using namespace Core;
using namespace Video;

namespace Components
{
	void RectangleRenderer::Start()
	{
		m_renderable.GetMaterial()->SetTexture(NULL);
		m_renderable.GetMaterial()->SetShader(Shader::GetFlatShader());
		m_renderable.GetMaterial()->SetColor(m_color);
		m_renderable.SetMesh(Mesh::GetFlatQuad());
		m_renderable.SetTransform(GetParent()->GetTransform());
		// VideoManager::GetInstance()->GetRenderDevice()->AddRenderable(&m_renderable);
	}
}