#include <iostream>

#include "SDLAdapter.h"

#include "..\Base\Exception.h"

SDLAdapter::SDLAdapter()
{
	m_SDLWindow = NULL;
}

SDLAdapter::~SDLAdapter()
{
	SDL_Quit();
}

void SDLAdapter::InitializeVideoSubsystem()
{
	int result = SDL_Init(SDL_INIT_VIDEO);

	if (result != 0)
	{
		throw Exception("SDL_Init failed");
	}
}

void SDLAdapter::CreateSDLWindow(int windowWidth, int windowHeight)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OpenGLContextMajorVersion);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OpenGLContextMinorVersion);
	m_SDLWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (m_SDLWindow == NULL)
	{
		throw Exception("SDL_CreateWindow failed");
	}
}

void SDLAdapter::CreateOpenGLContext()
{
	m_OpenGLContext = SDL_GL_CreateContext(m_SDLWindow);

	if (m_OpenGLContext == NULL) 
	{
		throw Exception("SDL_GL_CreateContext failed");
	}
}

void SDLAdapter::SetOpenGLSwapInterval(int interval)
{
	int result = SDL_GL_SetSwapInterval(1);

	if (result != 0)
	{
		// TODO: use a logger class
		std::cout << "Warning: GL_SetSwapInterval failed" << std::endl;
	}
}

void SDLAdapter::SwapOpenGLBuffers()
{
	SDL_GL_SwapWindow(m_SDLWindow);
}

bool SDLAdapter::HasPendingEvents()
{
	return SDL_PollEvent(NULL) == 1;
}

SDL_Event SDLAdapter::PollEvent()
{
	SDL_Event e;

	int result = SDL_PollEvent(&e);

	if (result == 0)
	{
		throw Exception("SDLAdapter::PollEvent has been called, but there are no events. Use SDLAdapter::HasPendingEvents before polling.");
	}

	return e;
}

void SDLAdapter::DestroyWindow()
{
	SDL_DestroyWindow(m_SDLWindow);
}

