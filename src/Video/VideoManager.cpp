#include "VideoManager.h"

#include "..\Base\SDLAdapter.h"
#include "..\Base\OpenGLAdapter.h"
#include "..\Base\Exception.h"
#include "..\Base\StringHelper.h"
using namespace Base;

#include "..\Input\InputManager.h"
using namespace Input;

#include <iostream>

namespace Video
{
	VideoManager* VideoManager::GetInstance()
	{
		static VideoManager instance;

		return &instance;
	}

	VideoManager::VideoManager() : m_defaultWindowSize(Vector2D(100.0f, 100.0f))
	{
		Initialize((int)m_defaultWindowSize.GetX(), (int)m_defaultWindowSize.GetY());
	}

	VideoManager::~VideoManager()
	{
		DeInitialize();
	}

	RenderDevice* VideoManager::GetRenderDevice()
	{
		return &m_renderDevice;
	}

	void VideoManager::SetWindowResolution(int windowWidth, int windowHeight)
	{
		DeInitialize();
		Initialize(windowWidth, windowHeight);
	}

	void VideoManager::InitializeSDLVideo(int windowWidth, int windowHeight)
	{
		SDLAdapter::InitializeVideoSubsystem();
		SDLAdapter::CreateSDLWindow(windowWidth, windowHeight);
		SDLAdapter::CreateOpenGLContext();
		SDLAdapter::SetOpenGLSwapInterval(1);
	}

	void VideoManager::InitializeOpenGL()
	{
		OpenGLAdapter::SetMatrixMode(GL_PROJECTION);
		OpenGLAdapter::SafeLoadIdentityMatrix();

		OpenGLAdapter::SetMatrixMode(GL_MODELVIEW);
		OpenGLAdapter::SafeLoadIdentityMatrix();

		OpenGLAdapter::SafeSetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// clear screen
	void VideoManager::ClearScreen()
	{
		OpenGLAdapter::ClearScreen();
	}

	// swap buffers
	void VideoManager::SwapBuffers()
	{
		SDLAdapter::SwapOpenGLBuffers();
	}


	void VideoManager::Initialize(int windowWidth, int windowHeight)
	{
		InitializeSDLVideo(windowWidth, windowHeight);

		InitializeOpenGL();
	}

	void VideoManager::DeInitialize()
	{
		SDLAdapter::QuitVideoSubsystem();
		SDLAdapter::DestroySDLWindow();
	}
}