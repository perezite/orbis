#pragma once

#include "RenderDevice.h"

namespace orb
{
	// manager for video functionality
	class VideoManager
	{
	public:
		static VideoManager* instance();

		RenderDevice* getRenderDevice() { return &m_renderDevice; }

	private:
		virtual ~VideoManager() { };

	private:
		RenderDevice m_renderDevice;
	};
}
