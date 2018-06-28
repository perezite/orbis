#include "RectangleRenderer.h"

#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"
using namespace orbis::core;
using namespace video;

namespace orbis
{
	namespace components
	{
		void RectangleRenderer::start()
		{
			m_renderable.getMaterial()->setTexture(NULL);
			m_renderable.getMaterial()->setShader(VideoManager::getInstance()->getShader("Shaders/Flat.vs", "Shaders/Flat.frag"));
			m_renderable.getMaterial()->setColor(m_color);
			m_renderable.setMesh(Mesh::createFlatQuad());
			m_renderable.setTransform(getParent()->getTransform());
			VideoManager::getInstance()->getRenderDevice()->addRenderable(&m_renderable);
		}
	}
}