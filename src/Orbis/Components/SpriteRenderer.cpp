#include "SpriteRenderer.h"

#include "../Video/VideoManager.h"
#include "../Core/TimeManager.h"

namespace orb
{
	SpriteRenderer::SpriteRenderer(Texture* texture)
		: Component()// , m_texture(texture)
	{
		throw Exception("deprecated!");
	}

	SpriteRenderer::SpriteRenderer(std::string assetPath)
	{
		m_texture = VideoManager::instance()->getTexture(assetPath);
	}

	void SpriteRenderer::start()
	{
		m_renderable.getMaterial()->setTexture(m_texture);
		m_renderable.getMaterial()->setShader(VideoManager::instance()->getShader("Shaders/Diffuse.vs", "Shaders/Diffuse.frag"));
		m_renderable.getMaterial()->setColor(Color::White);
		m_renderable.setMesh(Mesh::createTexturedQuad());
		m_renderable.setTransform(getParent()->getTransform());
		VideoManager::instance()->getRenderDevice()->addRenderable(&m_renderable);
	}

	void SpriteRenderer::setTexture(std::string path)
	{
		m_texture = VideoManager::instance()->getTexture(path);
		m_renderable.getMaterial()->setTexture(m_texture);
		VideoManager::instance()->getRenderDevice()->updateRenderable(&m_renderable);
	}

	void SpriteRenderer::setTexture(Texture * texture)
	{
		m_renderable.getMaterial()->setTexture(texture);
		VideoManager::instance()->getRenderDevice()->updateRenderable(&m_renderable);
	}
}