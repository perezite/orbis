#include "RectangleRenderer.h"

#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"
#include "../Game/Entity.h"

namespace orb
{
	void RectangleRenderer::start()
	{
		m_renderable.getMaterial()->setTexture(NULL);
		m_renderable.getMaterial()->setShader(VideoManager::instance().getShader("Shaders/Flat.vs", "Shaders/Flat.frag"));
		m_renderable.getMaterial()->setColor(m_color);
		m_renderable.setMesh(Mesh::createFlatQuad());
		m_renderable.setTransform(getParent()->getTransform());
		VideoManager::instance().getRenderDevice()->addRenderable(&m_renderable);
	}
}