#include "Particle.h"

#include "../Video/VideoManager.h"

namespace orb
{
	Particle::Particle(Texture * texture, const Color& color, const Transform & transform, const Vector2f & velocity)
		: m_renderable(NULL), m_transform(transform), m_velocity(velocity), m_lifetime(0.5f), m_color(color)
	{
		addRenderable(texture);
	}

	Particle::~Particle()
	{
		VideoManager::instance()->getRenderDevice();
		VideoManager::instance()->getRenderDevice()->deleteRenderable(m_renderable);
		delete m_renderable;
	}

	void Particle::addRenderable(Texture* texture)
	{
		m_renderable = new Renderable();
		m_renderable->getMaterial()->setTexture(texture);
		m_renderable->getMaterial()->setShader(VideoManager::instance()->getShader("Shaders/DiffuseParticle.vs", "Shaders/DiffuseParticle.frag"));
		m_renderable->setMesh(Mesh::createVertexColoredTexturedQuad(m_color));
		m_renderable->setTransform(&m_transform);
		VideoManager::instance()->getRenderDevice()->addRenderable(m_renderable);
	}
}