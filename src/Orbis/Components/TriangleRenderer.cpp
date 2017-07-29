#include "TriangleRenderer.h"

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
		// compute time delta in seconds
		static Uint32 previousTicks = SDL_GetTicks();
		Uint32 currentTicks = SDL_GetTicks();
		Uint32 elapsedTicks = currentTicks - previousTicks;
		previousTicks = SDL_GetTicks();
		float deltaTime = (float)elapsedTicks / 1000.0f;

		// set untransformed points
		Vector2D leftPoint(-0.3f, -0.3f);
		Vector2D rightPoint(0.3f, -0.3f);
		Vector2D topPoint(0.0f, 0.3f);

		// compute rotated points
		float omega = MathHelper::GetPi();
		static float alpha = 0.0f;
		alpha += omega * deltaTime;
		Vector2D rotatedLeftPoint(cos(alpha)*leftPoint.GetX() - sin(alpha)*leftPoint.GetY(), sin(alpha)*leftPoint.GetX() + cos(alpha)*leftPoint.GetY());
		Vector2D rotatedRightPoint(cos(alpha)*rightPoint.GetX() - sin(alpha)*rightPoint.GetY(), sin(alpha)*rightPoint.GetX() + cos(alpha)*rightPoint.GetY());
		Vector2D rotatedTopPoint(cos(alpha)*topPoint.GetX() - sin(alpha)*topPoint.GetY(), sin(alpha)*topPoint.GetX() + cos(alpha)*topPoint.GetY());

		// render
		Renderer* renderer = VideoManager::GetInstance()->GetRenderer();
		renderer->BeginPrimitive(RenderMode::Triangle);
			renderer->SetVertex2D(rotatedLeftPoint);
			renderer->SetVertex2D(rotatedRightPoint);
			renderer->SetVertex2D(rotatedTopPoint);
		renderer->EndPrimitive();
	}
}