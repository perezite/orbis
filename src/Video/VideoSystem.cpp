#include "VideoSystem.h"

#include "..\Base\Exception.h"
#include "..\Base\StringHelper.h"
using namespace Base;

#include "..\Input\InputManager.h"
using namespace Input;

#include <iostream>

namespace Video
{
	VideoSystem::VideoSystem(int windowWidth, int windowHeight)
	{
		m_openGLAdapter = new OpenGLAdapter();

		InitializeSDLVideo(windowWidth, windowHeight);

		InitializeOpenGL();
	}

	VideoSystem::~VideoSystem()
	{
		SDLAdapter::QuitVideoSubsystem();
		SDLAdapter::DestroySDLWindow();

		delete m_openGLAdapter;
	}

	void VideoSystem::InitializeSDLVideo(int windowWidth, int windowHeight)
	{
		SDLAdapter::InitializeVideoSubsystem();
		SDLAdapter::CreateSDLWindow(windowWidth, windowHeight);
		SDLAdapter::CreateOpenGLContext();
		SDLAdapter::SetOpenGLSwapInterval(1);
	}

	void VideoSystem::InitializeOpenGL()
	{
		m_openGLAdapter->SetMatrixMode(GL_PROJECTION);
		m_openGLAdapter->SafeLoadIdentityMatrix();

		m_openGLAdapter->SetMatrixMode(GL_MODELVIEW);
		m_openGLAdapter->SafeLoadIdentityMatrix();

		m_openGLAdapter->SafeSetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void VideoSystem::Update()
	{
		Render();

		SDLAdapter::SwapOpenGLBuffers();
	}

	// Just rendering a little test quad
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