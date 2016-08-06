#include "RenderDevice.h"

#include "..\Core\Exception.h"
using namespace Core;

namespace Video
{
	void RenderDevice::BeginPrimitive(RenderMode renderMode, bool textured)
	{
		m_texturedRendering = textured;
		if (m_texturedRendering)
			glEnable(GL_TEXTURE_2D);

		GraphicsAdapter::BeginPrimitive(renderMode);
	}

	void RenderDevice::EndPrimitive()
	{
		GraphicsAdapter::EndPrimitive();
		glDisable(GL_TEXTURE_2D);
	}

	void RenderDevice::SetTextureCoordinate(Vector2D position)
	{
		if (!m_texturedRendering)
			throw Exception("Setting textured coordinates is only valid when using textured rendering");

		glTexCoord2f((GLfloat)position.GetX(), (GLfloat)position.GetY());
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
