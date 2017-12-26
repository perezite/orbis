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
		m_material.SetShader(Shader::GetFlatShader());
		m_material.SetIsColorUsed(true);
		m_mesh = Mesh::GetFlatQuad();
		m_mesh->Initialize();
		GetParent()->GetTransform()->SetTransformSpace(TransformSpace::WorldSpace);
	}

	void RectangleRenderer::Render()
	{
		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();
		renderDevice->Render_old(GetParent()->GetTransform(), m_mesh, &m_material);
	}
}