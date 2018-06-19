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
	void DebugHelper::drawLine(Vector2D start, Vector2D end, Color color)
	{
		ORBIS_ASSERT_DEBUG();

		VideoManager::getInstance()->getRenderDevice()->drawDebugLine(start, end, color);
	}

	void DebugHelper::drawRect(Rect rect, Color color)
	{
		ORBIS_ASSERT_DEBUG();

		drawLine(rect.leftBottom, rect.GetRightBottom());
		drawLine(rect.GetRightBottom(), rect.rightTop);
		drawLine(rect.rightTop, rect.GetLeftTop());
		drawLine(rect.GetLeftTop(), rect.leftBottom);
	}

	void DebugHelper::drawSolidRect(Rect rect, Color color)
	{
		ORBIS_ASSERT_DEBUG();

		VideoManager::getInstance()->getRenderDevice()->drawDebugRect(rect, color);
	}
}