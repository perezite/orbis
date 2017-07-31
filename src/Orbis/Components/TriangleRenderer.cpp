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

namespace Components
{
	void TriangleRenderer::Update() { }

	void TriangleRenderer::Render()
	{
		// set untransformed points
		Vector2D leftPoint(-0.3f, -0.3f);
		Vector2D rightPoint(0.3f, -0.3f);
		Vector2D topPoint(0.0f, 0.3f);

		// compute rotated points
		static const float omega = MathHelper::GetPi();
		static float alpha = 0.0f;
		alpha += omega * TimeManager::GetInstance()->GetDeltaSeconds();

		Vector2D rotatedLeftPoint = leftPoint.Rotated(MathHelper::RadianToDegrees(alpha));
		Vector2D rotatedRightPoint = rightPoint.Rotated(MathHelper::RadianToDegrees(alpha));
		Vector2D rotatedTopPoint = topPoint.Rotated(MathHelper::RadianToDegrees(alpha));

		// render
		Renderer* renderer = VideoManager::GetInstance()->GetRenderer();
		renderer->BeginPrimitive(RenderMode::Triangle);
			renderer->SetVertex2D(rotatedLeftPoint);
			renderer->SetVertex2D(rotatedRightPoint);
			renderer->SetVertex2D(rotatedTopPoint);
		renderer->EndPrimitive();
	}
}