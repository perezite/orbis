#include "Renderable.h"
#include "VideoManager.h"

namespace orb
{
	Renderable::Renderable()
	{
		VideoManager::instance()->getRenderDevice()->enable(*this);
	}

	Renderable::~Renderable()
	{
		VideoManager::instance()->getRenderDevice()->disable(*this);
	}
}