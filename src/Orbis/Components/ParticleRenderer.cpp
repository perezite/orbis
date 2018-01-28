#include "ParticleRenderer.h"

#include "../Video/VideoManager.h"
using namespace Video;

namespace Components
{
	void ParticleRenderer::Start()
	{
		GetMaterial()->SetTexture(m_texture);
		GetMaterial()->SetShader(Shader::GetDiffuseShader());
		SetMesh(Mesh::GetTexturedQuad());
		m_transforms.push_back(Transform(Vector2D(-0.2f, -0.2f), 0.0f, Vector2D(0.1f, 0.1f)));
		m_transforms.push_back(Transform(Vector2D(+0.2f, -0.2f), 0.0f, Vector2D(0.1f, 0.1f)));
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);
	}
}
