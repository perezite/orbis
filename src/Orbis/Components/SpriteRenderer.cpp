#include "SpriteRenderer.h"

#include "../Orbis.h"
using namespace orb::video;
using namespace orb::core;

namespace orb
{
	namespace components
	{
		SpriteRenderer::SpriteRenderer(Texture* texture)
			: Component(), m_texture(texture)
		{}

		void SpriteRenderer::start()
		{
			m_renderable.getMaterial()->setTexture(m_texture);
			m_renderable.getMaterial()->setShader(VideoManager::getInstance()->getShader("Shaders/Diffuse.vs", "Shaders/Diffuse.frag"));
			m_renderable.getMaterial()->setColor(Color::White);
			m_renderable.setMesh(Mesh::createTexturedQuad());
			m_renderable.setTransform(getParent()->getTransform());
			VideoManager::getInstance()->getRenderDevice()->addRenderable(&m_renderable);
		}

		void SpriteRenderer::setTexture(Texture * texture)
		{
			m_renderable.getMaterial()->setTexture(texture);
			VideoManager::getInstance()->getRenderDevice()->updateRenderable(&m_renderable);
		}
	}
}