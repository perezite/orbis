#include "LineRenderer.h"

#include "../Game/Entity.h"
#include "../Video/VideoManager.h"
#include "../Video/Color.h"
using namespace Game;
using namespace Video;

#include "../../Base/Math/Vector2D.h"
using namespace Math;

namespace Components
{
	void LineRenderer::Start()
	{
		m_material.SetShader(Shader::GetFlatShader());
		m_material.SetColor(Color(1.0f, 0.0, 0.0f));
		m_material.SetIsColorUsed(true);
		m_mesh = Mesh::GetLineMesh();
		m_mesh->Initialize();
	}

	void LineRenderer::Render()
	{
		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();

		for (unsigned int i = 0; i < m_lines.size(); i++)
		{
			Vector2D begin = m_lines.at(i).first;
			Vector2D end = m_lines.at(i).second;

			float triangleHeight = end.GetY() - begin.GetY();
			float triangleWidth = end.GetX() - begin.GetX();
			float rotation = atan2(triangleHeight, triangleWidth);
			float length = (end - begin).GetLength();

			GetParent()->GetTransform()->position = begin;
			GetParent()->GetTransform()->rotation = rotation;
			GetParent()->GetTransform()->scale = Vector2D(length, 0.0f);

			renderDevice->Render_old(GetParent()->GetTransform(), m_mesh, &m_material);
		}
	}
}
