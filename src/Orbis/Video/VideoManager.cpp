#include "VideoManager.h"

#include "GraphicsAdapter.h"

#include "..\..\Base\System\Exception.h"
#include "..\..\Base\System\StringHelper.h"
using namespace System;

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
		InitializeVideo((int)m_defaultWindowSize.GetX(), (int)m_defaultWindowSize.GetY());
	}

	VideoManager::~VideoManager()
	{
		QuitVideo();
	}

	void VideoManager::InitializeVideo(int windowWidth, int windowHeight)
	{
		GraphicsAdapter::InitializeGraphics(windowWidth, windowHeight);

		GraphicsAdapter::SetMatrixMode(MatrixMode::Projection);
		GraphicsAdapter::SafeLoadIdentityMatrix();
		GraphicsAdapter::SetMatrixMode(MatrixMode::Modelview);
		GraphicsAdapter::SafeLoadIdentityMatrix();

		GraphicsAdapter::SafeSetClearColor(Color::Black);
	}

	void VideoManager::QuitVideo()
	{
		GraphicsAdapter::QuitGraphics();
	}

	void VideoManager::SetWindowResolution(int windowWidth, int windowHeight)
	{
		QuitVideo();
		InitializeVideo(windowWidth, windowHeight);
	}

	RenderDevice* VideoManager::GetRenderDevice()
	{
		return &m_renderDevice;
	}

	void VideoManager::ClearScreen()
	{
		GraphicsAdapter::ClearScreen();
	}

	void VideoManager::SwapBuffers()
	{
		GraphicsAdapter::SwapBuffers();
	}
}