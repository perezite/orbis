#include "SpriteRenderer.h"

#include "../Core\TimeManager.h"
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
		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();

		std::vector<Vector2D> vertices = { Vector2D(-0.5f, -0.5f), Vector2D(0.5f, -0.5f), Vector2D(-0.5f, 0.5f), Vector2D(0.5f, 0.5f) };
		std::vector<Vector2D> texCoords = { Vector2D(0.0f, 0.0f), Vector2D(1.0f, 0.0f), Vector2D(0.0f, 1.0f), Vector2D(1.0f, 1.0f) };
		std::vector<int> indices = { 0, 1, 2, 1, 3, 2 };
		renderDevice->AddGeometry(vertices, texCoords, indices);
	}

	void SpriteRenderer::Render()
	{
		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();
		renderDevice->Render(GetParent()->GetTransform(), m_texture, m_applyCameraTransformation);
	}
}