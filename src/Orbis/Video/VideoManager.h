#pragma once

#include "RenderDevice.h"

#include "..\..\Base\Math\Vector2D.h"
using namespace Math;

#include "..\Game\Entity.h"
using namespace Game;

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

		// initialize SDL
		void InitializeVideo(int windowWidth, int windowHeight);

	private:
		// window size
		const Vector2D m_defaultWindowSize;

		// render device
		RenderDevice m_renderDevice;

	};
}