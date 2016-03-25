#include "RenderDevice.h"

#include "GraphicsAdapter.h"

namespace Video
{
	void RenderDevice::BeginPrimitive()
	{
		GraphicsAdapter::BeginPrimitive(RenderMode::Quads);
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
