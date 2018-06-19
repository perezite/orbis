#include "DebugHelper.h"

#include "../Video/VideoManager.h"
using namespace Video;

#ifndef _DEBUG 
	#define ORBIS_ASSERT_DEBUG() \
		throw Exception("Debug functionality can only be called in debug mode"); 
#else	
	#define ORBIS_ASSERT_DEBUG() 
#endif


namespace Core
{
	void DebugHelper::DrawLine(Vector2D start, Vector2D end, Color color)
	{
		ORBIS_ASSERT_DEBUG();

		VideoManager::getInstance()->getRenderDevice()->DrawDebugLine(start, end, color);
	}

	void DebugHelper::DrawRect(Rect rect, Color color)
	{
		ORBIS_ASSERT_DEBUG();

		DrawLine(rect.leftBottom, rect.GetRightBottom());
		DrawLine(rect.GetRightBottom(), rect.rightTop);
		DrawLine(rect.rightTop, rect.GetLeftTop());
		DrawLine(rect.GetLeftTop(), rect.leftBottom);
	}

	void DebugHelper::DrawSolidRect(Rect rect, Color color)
	{
		ORBIS_ASSERT_DEBUG();

		VideoManager::getInstance()->getRenderDevice()->DrawDebugRect(rect, color);
	}
}