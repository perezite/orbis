#include "DebugHelper.h"

#include "../Video/VideoManager.h"
using namespace Video;

namespace Core
{
	void DebugHelper::DrawLine(Vector2D start, Vector2D end, Color color)
	{
		#ifndef _DEBUG
			throw Exception("DebugHelper::DrawLine(): Debug functionality can only be called in debug mode");
		#endif

		VideoManager::GetInstance()->GetRenderDevice()->DrawDebugLine(start, end, color);
	}

	void DebugHelper::DrawSolidRect(Rect rect, Color color)
	{
		#ifndef _DEBUG
			throw Exception("DebugHelper::DrawRectangle(): Debug functionality can only be called in debug mode");
		#endif

		VideoManager::GetInstance()->GetRenderDevice()->DrawDebugRect(rect, color);
	}
}