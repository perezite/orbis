#include "ShapeRenderer.h"
#include "../video/VideoManager.h"

namespace orb 
{
	void ShapeRenderer::render()
	{
		VideoManager::instance()->getRenderDevice()->render(m_mesh);
	}
}
