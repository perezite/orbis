#include "SpriteRenderer.h"

#include "..\Core\TimeManager.h"
using namespace Core;

#include "..\Video\VideoManager.h"
using namespace Video;

#include "..\Game\Entity.h"
using namespace Game;

#include "..\..\Base\Math\MathHelper.h"
#include "..\..\Base\System\Exception.h"
using namespace Math;
using namespace System;

#include <math.h>
#include <iostream>

namespace Components
{
	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Start()
	{
		RenderDevice* renderer = VideoManager::GetInstance()->GetRenderer();

		std::vector<Vector2D> vertices = { Vector2D(-0.3f, -0.3f), Vector2D(0.3f, -0.3f), Vector2D(-0.3f, 0.3f), Vector2D(0.3f, 0.3f) };
		std::vector<Vector2D> texCoords = { Vector2D(0.0f, 0.0f), Vector2D(1.0f, 0.0f), Vector2D(0.0f, 1.0f), Vector2D(1.0f, 1.0f) };
		std::vector<int> indices = { 0, 1, 2, 1, 3, 2 };
		renderer->AddGeometry(vertices, texCoords, indices);
	}

	void SpriteRenderer::Render()
	{
		RenderDevice* renderer = VideoManager::GetInstance()->GetRenderer();
		static const float omega = MathHelper::GetPi();

		Transform* transform = GetParent()->GetTransform();
		float alpha = transform->GetRotation();
		transform->SetRotation(alpha + TimeManager::GetInstance()->GetDeltaSeconds() * omega);

		renderer->Render(GetParent()->GetTransform());
	}
}