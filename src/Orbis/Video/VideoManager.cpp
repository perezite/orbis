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
	const Vector2D VideoManager::m_DefaultWindowResolution(400.0f, 400.0f);

	VideoManager* VideoManager::GetInstance()
	{
		static VideoManager instance;
		return &instance;
	}

	VideoManager::VideoManager()
	{
		m_renderer = NULL;

		InitializeVideo();
	}

	VideoManager::~VideoManager()
	{
		if (m_renderer)
			delete m_renderer;
		SDL_DestroyWindow(m_sdlWindow);
		SDL_Quit();
	}

	RenderDevice* VideoManager::GetRenderer()
	{
		if (m_renderer == NULL)
			m_renderer = new RenderDevice();

		return m_renderer;
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

	void VideoManager::InitializeVideo()
	{
		SDL_Init(SDL_INIT_VIDEO);
		m_windowResolution = GetDefaultWindowResolution();

		#ifdef WIN32	
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			m_sdlWindow = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)m_windowResolution.GetX(), (int)m_windowResolution.GetY(), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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
			m_sdlWindow = SDL_CreateWindow(NULL, 0, 0, (int)m_windowResolution.GetX(), (int)m_windowResolution.GetY(), SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
			m_openGlContext = SDL_GL_CreateContext(m_sdlWindow);
		#endif

		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		glViewport(0, 0, (int)m_windowResolution.GetX(), (int)m_windowResolution.GetY());

	}

	Vector2D VideoManager::GetDefaultWindowResolution()
	{
		if (EnvironmentHelper::IsMobile())
		{
			SDL_DisplayMode mode;
			SDL_GetDisplayMode(0, 0, &mode);
			return Vector2D((float)mode.w, (float)mode.h);
		}

		else return m_DefaultWindowResolution;
	}
}