#include "DebugUtil.h"

#include "../Video/VideoManager.h"

#ifndef _DEBUG 
#	define ORBIS_ASSERT_DEBUG() \
		throw Exception("Debug functionality can only be called in debug mode"); 
#else	
	#define ORBIS_ASSERT_DEBUG() 
#endif

namespace orb
{
	void DebugUtil::drawLine(Vector2f start, Vector2f end, Color color)
	{
		ORBIS_ASSERT_DEBUG();

		VideoManager::instance().getDebugRenderDevice()->drawDebugLine(start, end, color);
	}

	void DebugUtil::drawRect(Rect rect, Color color)
	{
		ORBIS_ASSERT_DEBUG();

		drawLine(rect.leftBottom, rect.getRightBottom());
		drawLine(rect.getRightBottom(), rect.rightTop);
		drawLine(rect.rightTop, rect.getLeftTop());
		drawLine(rect.getLeftTop(), rect.leftBottom);
	}

	void DebugUtil::drawSolidRect(Rect rect, Color color)
	{
		ORBIS_ASSERT_DEBUG();

		VideoManager::instance().getDebugRenderDevice()->drawDebugRect(rect, color);
	}
}