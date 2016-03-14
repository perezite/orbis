#include <iostream>

#include "VideoSystem.h"
#include "..\Base\Exception.h"
#include "..\Base\StringHelper.h"
#include "..\Base\SDLAdapter.h"
#include "..\Base\OpenGLAdapter.h"

namespace Video
{
	VideoSystem::VideoSystem(int windowWidth, int windowHeight)
	{
		m_openGLAdapter = new OpenGLAdapter();
		m_SDLAdapter = new SDLAdapter();

		InitializeSDL(windowWidth, windowHeight);

		InitializeOpenGL();
	}

	VideoSystem::~VideoSystem()
	{
		m_SDLAdapter->DestroyWindow();

		delete m_SDLAdapter;
		delete m_openGLAdapter;
	}

	void VideoSystem::InitializeSDL(int windowWidth, int windowHeight)
	{
		m_SDLAdapter->InitializeVideoSubsystem();
		m_SDLAdapter->CreateSDLWindow(windowWidth, windowHeight);
		m_SDLAdapter->CreateOpenGLContext();
		m_SDLAdapter->SetOpenGLSwapInterval(1);
	}

	void VideoSystem::InitializeOpenGL()
	{
		m_openGLAdapter->SetMatrixMode(GL_PROJECTION);
		m_openGLAdapter->SafeLoadIdentityMatrix();

		m_openGLAdapter->SetMatrixMode(GL_MODELVIEW);
		m_openGLAdapter->SafeLoadIdentityMatrix();

		m_openGLAdapter->SafeSetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void VideoSystem::Run()
	{
		bool quit = false;
		SDL_Event e;

		while (quit == false)
		{
			while (m_SDLAdapter->HasPendingEvents())
			{
				e = m_SDLAdapter->PollEvent();

				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}

			Render();

			m_SDLAdapter->SwapOpenGLBuffers();
		}
	}

	void VideoSystem::Render()
	{
		m_openGLAdapter->ClearScreen();

		m_openGLAdapter->BeginPrimitive(GL_QUADS);
		m_openGLAdapter->SetVertex2D(-0.5f, -0.5f);
		m_openGLAdapter->SetVertex2D(0.5f, -0.5f);
		m_openGLAdapter->SetVertex2D(0.5f, 0.5f);
		m_openGLAdapter->SetVertex2D(-0.5f, 0.5f);
		m_openGLAdapter->EndPrimitive();
	}

}