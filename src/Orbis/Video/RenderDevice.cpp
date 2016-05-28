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

	void RenderDevice::ApplyGlobalTranslation(Vector2D translation)
	{
		GraphicsAdapter::ApplyGlobalTranslation(translation);
	}

	void RenderDevice::ApplyGlobalScale(Vector2D scale)
	{
		GraphicsAdapter::ApplyGlobalScale(scale);
	}

	void RenderDevice::ApplyGlobalRotation(float rotation)
	{
		GraphicsAdapter::ApplyGlobalRotation(rotation);
	}

	void RenderDevice::ResetGlobalTransforms()
	{
		GraphicsAdapter::LoadIdentityMatrix();
	}
}
