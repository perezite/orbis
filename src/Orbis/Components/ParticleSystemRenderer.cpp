#include "ParticleSystemRenderer.h"

#include "../../Orbis/Video/VideoManager.h"
using namespace Video;

namespace Components
{
	void ParticleSystemRenderer::Start()
	{
		GetMaterial()->SetTexture(m_texture);
		GetMaterial()->SetShader(Shader::GetDiffuseShader());
		SetMesh(Mesh::GetTexturedQuad());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);
	}
}
