#include "VideoManager.h"

#include "../Libraries/GL.h"
#include "../Libraries/SDL.h"

#include "../../Base/System/Exception.h"
#include "../../Base/System/StringHelper.h"
#include "../../Base/System/EnvironmentHelper.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/MathHelper.h"
using namespace Math;
using namespace System;

#include <iostream>

namespace Video
{
	const Vector2D VideoManager::DESKTOP_DEFAULT_RESOLUTION(400, 711);

	VideoManager* VideoManager::GetInstance()
	{
		static VideoManager instance;
		return &instance;
	}

	VideoManager::VideoManager()
	{
		Initialize();
	}

	VideoManager::~VideoManager()
	{
		Shutdown();
	}

	void VideoManager::SetResolution(Vector2D resolution)
	{
		if (EnvironmentHelper::IsMobile())
			return;

		SDL_DestroyWindow(m_sdlWindow);
		m_windowResolution = resolution;
		CreateSdlWindow();

		SDL_GL_MakeCurrent(m_sdlWindow, m_openGlContext);
		glViewport(0, 0, (int)m_windowResolution.x, (int)m_windowResolution.y);
	}

	void VideoManager::ClearScreen()
	{
		glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void VideoManager::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_sdlWindow);
	}

	void VideoManager::Shutdown()
	{
		SDL_GL_DeleteContext(m_openGlContext);
		SDL_DestroyWindow(m_sdlWindow);
		SDL_Quit();
		m_isInitialized = false;
	}

	void VideoManager::Initialize(bool useDefaultResolution)
	{
		if (m_isInitialized)
			return;

		SDL_Init(SDL_INIT_VIDEO);
		m_windowResolution = useDefaultResolution ? GetDefaultWindowResolution() : m_windowResolution;

#ifdef WIN32	
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		CreateSdlWindow();		
		m_openGlContext = SDL_GL_CreateContext(m_sdlWindow);
		glewInit();
#endif	
#ifdef __ANDROID__
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		CreateSdlWindow();
		m_openGlContext = SDL_GL_CreateContext(m_sdlWindow);
#endif

		glViewport(0, 0, (int)m_windowResolution.x, (int)m_windowResolution.y);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		m_isInitialized = true;
	}

	Vector2D VideoManager::GetDefaultWindowResolution()
	{
		if (EnvironmentHelper::IsMobile())
		{
			SDL_DisplayMode mode;
			SDL_GetDisplayMode(0, 0, &mode);
			return Vector2D((float)mode.w, (float)mode.h);
		}

		else return DESKTOP_DEFAULT_RESOLUTION;
	}

	void VideoManager::CreateSdlWindow()
	{
#ifdef WIN32
		m_sdlWindow = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)m_windowResolution.x, (int)m_windowResolution.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
#endif
#ifdef __ANDROID__
		m_sdlWindow = SDL_CreateWindow(NULL, 0, 0, (int)m_windowResolution.x, (int)m_windowResolution.y, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
#endif


	}
}