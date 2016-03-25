#pragma once

#include "RenderDevice.h"

#include "..\Core\Entity.h"
using namespace Core;

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

		// set resolution
		void SetWindowResolution(int widthInPixels, int heightInPixels);

		// render
		void Render(std::vector<Entity*> &entities);

		// clear screen
		void ClearScreen();

		// swap buffers
		void SwapBuffers();

	protected:
		// default singleton constructor
		VideoManager();

		// initialize video system
		void Initialize(int windowWidth, int windowHeight);

		// deinitialize video system
		void DeInitialize();

		// initialize SDL
		void InitializeSDLVideo(int windowWidth, int windowHeight);

		// initialize OpenGL
		void InitializeOpenGL();
	private:
		// window size
		const Vector2D m_defaultWindowSize;

		// render device
		RenderDevice m_renderDevice;

	};
}