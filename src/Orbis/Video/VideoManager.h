#pragma once

#include "RenderDevice.h"

#include "..\Game\Entity.h"
using namespace Game;

#include "..\Math\Vector2D.h"
using namespace Math;

namespace Video
{
	class VideoManager
	{
	public:
		// get instance
		static VideoManager* GetInstance();

		// destructor
		virtual ~VideoManager();

		// get the render device
		RenderDevice* GetRenderDevice();

		// initialize SDL
		void InitializeVideo(int windowWidth, int windowHeight);

		// quit video
		void QuitVideo();

		// set resolution
		void SetWindowResolution(int widthInPixels, int heightInPixels);

		// clear screen
		void ClearScreen();

		// swap buffers
		void SwapBuffers();

	protected:
		// singleton constructor
		VideoManager();

	private:
		// window size
		const Vector2D m_defaultWindowSize;

		// render device
		RenderDevice m_renderDevice;

	};
}