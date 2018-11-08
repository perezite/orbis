#include "Renderable.h"
#include "VideoManager.h"

namespace orb
{
	Renderable::Renderable(unsigned int numVertices) 
		: m_mesh(numVertices)
	{
		VideoManager::instance()->getRenderDevice()->enable(*this);
	}

	Renderable::~Renderable()
	{
		VideoManager::instance()->getRenderDevice()->disable(*this);
	}
}