#include "RectangleRenderer.h"

#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"
#include "../Video/Mesh.h"
#include "../Game/Entity.h"
using namespace Core;
using namespace Video;
using namespace Game;

#include "../../Base/Math/MathHelper.h"
#include "../../Base/System/Exception.h"
using namespace Math;
using namespace System;

#include <math.h>
#include <iostream>

namespace Components
{
	void RectangleRenderer::Start()
	{
		m_shader = Shader::GetFlatShader();
		m_mesh = Mesh::GetFlatQuad();
		m_mesh->Initialize();
	}

	void RectangleRenderer::Render()
	{
		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();
		renderDevice->Render(m_mesh, GetParent()->GetTransform(), NULL, m_shader, m_color, RenderMode::Triangles, true, false);
	}
}