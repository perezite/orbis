#include "RenderDevice.h"

#include "Shader.h"
#include "VideoManager.h"

#include "../Components/Camera.h"
#include "../Core/LogUtil.h"
#include "../Engine/Settings.h"

#include <algorithm>

namespace orb
{
	void DebugRenderDevice::drawDebugLine(Vector2D start, Vector2D end, Color color)
	{
		// compute vertex array
		Matrix3 camMatrix = Camera::getInstance()->getCamMatrix();
		start = camMatrix * start;
		end = camMatrix * end;
		GLfloat vertexArray[4] = { start.x, start.y, end.x, end.y };

		glLineWidth(3);
		drawDebugPrimitive(vertexArray, 4, color, RenderMode::Lines);
	}

	void DebugRenderDevice::drawDebugRect(Rect rect, Color color)
	{
		// compute vertex array
		Matrix3 camMatrix = Camera::getInstance()->getCamMatrix();
		rect = camMatrix * rect;
		GLfloat vertexArray[12] = {
			rect.leftBottom.x , rect.leftBottom.y, rect.getRightBottom().x, rect.getRightBottom().y, rect.getLeftTop().x, rect.getLeftTop().y,
			rect.getRightBottom().x, rect.getRightBottom().y, rect.rightTop.x, rect.rightTop.y, rect.getLeftTop().x, rect.getLeftTop().y
		};

		drawDebugPrimitive(vertexArray, 12, color, RenderMode::Triangles);
	}

	void DebugRenderDevice::drawDebugPrimitive(GLfloat * vertexArray, unsigned int vertexArrayCount, Color color, RenderMode renderMode)
	{
		// prepare
		glDisable(GL_BLEND);
		Shader* shader = VideoManager::getInstance()->getShader("Shaders/Flat.vs", "Shaders/Flat.frag");
		shader->use();
		shader->setUniform("u_vColor", color);
		int positionAttribLocation = shader->getAttributeLocation("a_vPosition");
		glEnableVertexAttribArray(positionAttribLocation);
		glVertexAttribPointer(positionAttribLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), vertexArray);

		// draw
		glDrawArrays((GLenum)renderMode, 0, vertexArrayCount / 2);

		// cleanup
		glDisableVertexAttribArray(positionAttribLocation);
		shader->unuse();
	}
}
