#include "RenderDevice.h"

namespace Video
{
	void RenderDevice::BeginPrimitive(RenderMode renderMode)
	{
		GraphicsAdapter::BeginPrimitive(renderMode);
	}

	void RenderDevice::EndPrimitive()
	{
		GraphicsAdapter::EndPrimitive();
	}

	void RenderDevice::SetVertex2D(Vector2D position)
	{
		GraphicsAdapter::SetVertex2D(position);
	}
}
