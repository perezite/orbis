#include "RenderDevice.h"

#include "..\Base\OpenGLAdapter.h"
using namespace Base;

namespace Video
{
	void RenderDevice::BeginPrimitive()
	{
		OpenGLAdapter::BeginPrimitive(GL_QUADS);
	}

	void RenderDevice::EndPrimitive()
	{
		OpenGLAdapter::EndPrimitive();
	}

	void RenderDevice::SetVertex2D(Vector2D position)
	{
		OpenGLAdapter::SetVertex2D(position.GetX(), position.GetY());
	}
}
