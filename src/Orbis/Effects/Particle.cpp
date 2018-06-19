#include "Particle.h"

#include "../Video/VideoManager.h"
using namespace Video;

namespace Effects
{
	Particle::Particle(Texture * texture, const Color& color, const Transform & transform, const Vector2D & velocity) 
		: m_renderable(NULL), m_transform(transform),  m_velocity(velocity), m_lifetime(0.5f), m_color(color)
	{
		addRenderable(texture);
	}

	Particle::~Particle()
	{
		VideoManager::getInstance()->getRenderDevice()->deleteRenderable(m_renderable);
		delete m_renderable;
	}

	void Particle::addRenderable(Texture* texture)
	{
		m_renderable = new Renderable();
		m_renderable->getMaterial()->setTexture(texture);
		m_renderable->getMaterial()->setShader(VideoManager::getInstance()->getShader("Shaders/DiffuseParticle.vs", "Shaders/DiffuseParticle.frag"));
		m_renderable->setMesh(Mesh::createVertexColoredTexturedQuad(m_color));
		m_renderable->setTransform(&m_transform);
		VideoManager::getInstance()->getRenderDevice()->addRenderable(m_renderable);
	}
}