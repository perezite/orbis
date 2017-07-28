#include "VideoManager.h"

#include "../../Base/System/Exception.h"
#include "../../Base/System/StringHelper.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/MathHelper.h"
#include "../../Base/System/EnvironmentHelper.h"
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
		m_windowResolution = GetDefaultWindowResolution();
		InitializeVideo();
		m_renderDevice.SetWindowResolution(m_windowResolution);
		m_renderDevice.Initialize();
	}

	void VideoManager::Run()
	{
		bool quit = false;
		SDL_Event e;
		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN || e.type == SDL_FINGERDOWN)
					quit = true;
			}

			RenderTriangle();
			SwapBuffers();
		}
	}

	void VideoManager::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_sdlWindow);
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

	void VideoManager::InitializeVideo()
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

		// os specific intialization
		#ifdef WIN32		
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			m_sdlWindow = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)m_windowResolution.GetX(), (int)m_windowResolution.GetY(), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
			m_openGlContext = SDL_GL_CreateContext(m_sdlWindow);
			glewInit();
			SDL_GL_SetSwapInterval(1);
		#endif	
		#ifdef __ANDROID__
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			m_sdlWindow = SDL_CreateWindow("Example", 0, 0, (int)m_windowResolution.GetX(), (int)m_windowResolution.GetY(), SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);			m_openGlContext = SDL_GL_CreateContext(m_sdlWindow);

		#endif
	}

	void VideoManager::RenderTriangle()
	{
		// compute time delta in seconds
		static Uint32 previousTicks = SDL_GetTicks();
		Uint32 currentTicks = SDL_GetTicks();
		Uint32 elapsedTicks = currentTicks - previousTicks;
		previousTicks = SDL_GetTicks();
		float deltaTime = (float)elapsedTicks / 1000.0f;

		// set untransformed points
		// const float z = 0.0f;
		Vector2D leftPoint(-0.3f, -0.3f);
		Vector2D rightPoint(0.3f, -0.3f);
		Vector2D topPoint(0.0f, 0.3f);

		// compute rotated points
		float omega = MathHelper::GetPi();
		static float alpha = 0.0f;
		alpha += omega * deltaTime;
		Vector2D rotatedLeftPoint(cos(alpha)*leftPoint.GetX() - sin(alpha)*leftPoint.GetY(), sin(alpha)*leftPoint.GetX() + cos(alpha)*leftPoint.GetY());
		Vector2D rotatedRightPoint(cos(alpha)*rightPoint.GetX() - sin(alpha)*rightPoint.GetY(), sin(alpha)*rightPoint.GetX() + cos(alpha)*rightPoint.GetY());
		Vector2D rotatedTopPoint(cos(alpha)*topPoint.GetX() - sin(alpha)*topPoint.GetY(), sin(alpha)*topPoint.GetX() + cos(alpha)*topPoint.GetY());

		m_renderDevice.BeginPrimitive(RenderMode::Triangle);
		m_renderDevice.SetVertex2D(rotatedLeftPoint);
		m_renderDevice.SetVertex2D(rotatedRightPoint);
		m_renderDevice.SetVertex2D(rotatedTopPoint);
		m_renderDevice.EndPrimitive();
	}

	VideoManager::~VideoManager()
	{
		SDL_DestroyWindow(m_sdlWindow);
		SDL_Quit();
	}

	RenderDevice* VideoManager::GetRenderDevice()
	{
		return &m_renderDevice;
	}
}