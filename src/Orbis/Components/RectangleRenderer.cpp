#include "RectangleRenderer.h"

#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"
using namespace Core;
using namespace Video;

namespace Components
{
	void RectangleRenderer::start()
	{
		m_renderable.getMaterial()->setTexture(NULL);
		m_renderable.getMaterial()->setShader(VideoManager::getInstance()->getShader("Shaders/Flat.vs", "Shaders/Flat.frag"));
		m_renderable.getMaterial()->setColor(m_color);
		m_renderable.setMesh(Mesh::createFlatQuad());
		m_renderable.setTransform(GetParent()->getTransform());
		VideoManager::getInstance()->getRenderDevice()->addRenderable(&m_renderable);
	}
}