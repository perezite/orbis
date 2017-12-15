#include "SpriteRenderer.h"

#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"
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
	void SpriteRenderer::Start()
	{
		m_shader = new Shader("Shaders/Diffuse.vs", "Shaders/Diffuse.frag");
		m_mesh = &Mesh::TexturedQuad;
		m_mesh->Initialize();
	}

	void SpriteRenderer::Render()
	{
		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();
		renderDevice->Render(m_mesh, GetParent()->GetTransform(), m_texture, m_shader, Color::White, RenderMode::Triangles, false, m_applyCameraTransformation);
	}
}