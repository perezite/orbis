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
		m_shader = Shader::GetFlatShader();
		m_mesh = new Mesh(
			{ Vector2D(0.0f, 0.0f), Vector2D(1.0f, 0.0f)}, 
			{}, 
			{ 1, 2 }
		);
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

			GetParent()->GetTransform()->SetPosition(begin);
			GetParent()->GetTransform()->SetRotation(rotation);
			GetParent()->GetTransform()->SetScale(Vector2D(length, 0.0f));

			renderDevice->Render(m_mesh, GetParent()->GetTransform(), NULL, m_shader, Color(1.0f, 0.0f, 0.0f), RenderMode::Lines, true, false);
		}
	}
}
