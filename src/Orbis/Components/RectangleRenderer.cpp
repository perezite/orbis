#include "RectangleRenderer.h"

#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"
using namespace Core;
using namespace Video;

namespace Components
{
	void RectangleRenderer::Start()
	{
		Renderer::Start();

		GetMaterial()->SetTexture(NULL);
		GetMaterial()->SetShader(Shader::GetFlatShader());
		GetMaterial()->SetColor(m_color);
		SetMesh(Mesh::GetFlatQuad());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);
	}
}