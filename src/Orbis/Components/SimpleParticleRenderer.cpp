#include "SimpleParticleRenderer.h"

#include "TweenInspector.h"

#include "../Video/VideoManager.h"
#include "../Core/TimeManager.h"
#include "../Game/LevelManager.h"
using namespace Video;
using namespace Core;
using namespace Game;

#include "../../Base/Math/MathHelper.h"
using namespace Math;

namespace Components
{
	SimpleParticleRenderer::SimpleParticleRenderer(Texture * texture) : m_texture(texture)
	{
	}

	void SimpleParticleRenderer::Start()
	{
		GetMaterial()->SetTexture(m_texture);
		GetMaterial()->SetColor(Color(1.0f, 1.0f, 1.0f, 0.5f));
		GetMaterial()->SetShader(Shader::GetDiffuseShader());
		SetMesh(Mesh::GetTexturedQuad());
		m_particles.push_back(Particle(Transform(Vector2D(-0.1f, -0.1f), 0.0f, Vector2D(0.1f, 0.1f)), Vector2D::Zero));
		m_particles.push_back(Particle(Transform(Vector2D(+0.1f, -0.1f), 0.0f, Vector2D(0.1f, 0.1f)), Vector2D::Zero));
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);
	}

	std::vector<Transform> SimpleParticleRenderer::GetRenderTransforms()
	{
		std::vector<Transform> transforms;
		for (unsigned int i = 0; i < m_particles.size(); i++)
			transforms.push_back(m_particles[i].GetTransform());

		return transforms;
	}
}
