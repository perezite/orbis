#include "TriangleRenderer.h"

#include "..\Core\TimeManager.h"
using namespace Core;

#include "..\Video\VideoManager.h"
using namespace Video;

#include "..\Game\Entity.h"
using namespace Game;

#include "..\..\Base\Math\MathHelper.h"
using namespace Math;

#include <math.h>
#include <iostream>

namespace Components
{
	TriangleRenderer::~TriangleRenderer()
	{
	}

	void TriangleRenderer::Start()
	{
		Renderer* renderer = VideoManager::GetInstance()->GetRenderer();

		std::vector<Vector2D> vertices = { Vector2D(-0.3f, -0.3f), Vector2D(0.3f, -0.3f), Vector2D(-0.3f, 0.3f), Vector2D(0.3f, 0.3f) };
		std::vector<Vector2D> texCoords = { Vector2D(0.0f, 0.0f), Vector2D(1.0f, 0.0f), Vector2D(0.0f, 1.0f), Vector2D(1.0f, 1.0f) };
		std::vector<int> indices = { 0, 1, 2, 1, 3, 2 };
		renderer->AddGeometry(vertices, texCoords, indices);
	}

	void TriangleRenderer::Render()
	{
		static Renderer* renderer = VideoManager::GetInstance()->GetRenderer();
		static const float omega = MathHelper::GetPi();
		static float alpha = 0.0f;

		alpha += omega * TimeManager::GetInstance()->GetDeltaSeconds();
		renderer->Render(alpha);
	}
}