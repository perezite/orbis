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

		std::vector<Vector2D> vertexData = { Vector2D(-0.3f, -0.3f), Vector2D(0.3f, -0.3f), Vector2D(0.0f,  0.3f) };
		int indexData[] = { 0, 1, 2 };
		renderer->AddGeometry(vertexData, indexData);
	}

	void TriangleRenderer::Render()
	{
		static Renderer* renderer = VideoManager::GetInstance()->GetRenderer();
		static const float omega = MathHelper::GetPi() * 20.0f;
		static float alpha = 0.0f;

		alpha += omega * TimeManager::GetInstance()->GetDeltaSeconds();
		renderer->Render(alpha);
	}
}