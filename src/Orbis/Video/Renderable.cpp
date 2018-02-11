#include "Renderable.h"

#include "../Video/VideoManager.h"
using namespace Video;

namespace Video
{
	Renderable::Renderable()
	{
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderable(this);
	}

	Renderable::~Renderable()
	{
		VideoManager::GetInstance()->GetRenderDevice()->DeleteRenderable(this);
	}

	void Renderable::Update()
	{
		VideoManager::GetInstance()->GetRenderDevice()->UpdateRenderable(this);
	}
}
