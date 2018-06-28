#include "DebugHelper.h"

#include "../Video/VideoManager.h"
using namespace video;

#ifndef _DEBUG 
	#define ORBIS_ASSERT_DEBUG() \
		throw Exception("Debug functionality can only be called in debug mode"); 
#else	
	#define ORBIS_ASSERT_DEBUG() 
#endif

namespace orbis
{
	namespace core
	{
		void DebugHelper::drawLine(Vector2D start, Vector2D end, Color color)
		{
			ORBIS_ASSERT_DEBUG();

			VideoManager::getInstance()->getDebugRenderDevice()->drawDebugLine(start, end, color);
		}

		void DebugHelper::drawRect(Rect rect, Color color)
		{
			ORBIS_ASSERT_DEBUG();

			drawLine(rect.leftBottom, rect.getRightBottom());
			drawLine(rect.getRightBottom(), rect.rightTop);
			drawLine(rect.rightTop, rect.getLeftTop());
			drawLine(rect.getLeftTop(), rect.leftBottom);
		}

		void DebugHelper::drawSolidRect(Rect rect, Color color)
		{
			ORBIS_ASSERT_DEBUG();

			VideoManager::getInstance()->getDebugRenderDevice()->drawDebugRect(rect, color);
		}
	}
}