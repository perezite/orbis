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
		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();
		m_shader = new Shader("Shaders/Flat.vs", "Shaders/Flat.frag");

		//std::vector<Vector2D> vertices = { Vector2D(-0.5f, -0.5f), Vector2D(0.5f, -0.5f), Vector2D(-0.5f, 0.5f), Vector2D(0.5f, 0.5f) };
		//std::vector<Vector2D> texCoords = { Vector2D(0.0f, 0.0f), Vector2D(1.0f, 0.0f), Vector2D(0.0f, 1.0f), Vector2D(1.0f, 1.0f) };	
		//std::vector<int> indices = { 0, 1, 2, 1, 3, 2 };
		m_mesh = &Mesh::FlatQuad;
		m_mesh->Initialize();
	}

	void RectangleRenderer::Render()
	{
		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();
		renderDevice->Render(m_mesh, GetParent()->GetTransform(), NULL, m_shader, m_color, RenderMode::Triangles, true, false);
	}
}