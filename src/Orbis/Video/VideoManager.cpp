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
	const Vector2D VideoManager::m_DefaultWindowResolution(400.0f, 711.0f);

	VideoManager* VideoManager::GetInstance()
	{
		static VideoManager instance;
		return &instance;
	}

	VideoManager::VideoManager() 
		: m_isIndexArrayDirty(false)
	{
		Initialize();
	}

	VideoManager::~VideoManager()
	{
		SDL_DestroyWindow(m_sdlWindow);
		SDL_Quit();
	}

	void VideoManager::AddRenderer(Renderer* renderer)
	{
		int position = FindFirstIndexInBatch(renderer);
		m_renderers.insert(m_renderers.begin() + position, renderer);
		m_isIndexArrayDirty = true;
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

	void VideoManager::UpdateIndexArray()
	{
		if (m_isIndexArrayDirty)
		{
			m_indexArray.clear();
			ReserveIndexArray();

			unsigned int totalNumIndices = 0;
			GLushort valueOffset = 0;
			for (unsigned int i = 0; i < m_renderers.size(); i++)
			{
				Mesh_v2* mesh = m_renderers[i]->GetMesh();
				for (unsigned int j = 0; j < mesh->GetIndices()->size(); j++)
				{
					GLushort value = mesh->GetIndices()->at(j) + valueOffset;
					m_indexArray.insert(m_indexArray.begin() + totalNumIndices, value);
					totalNumIndices++;
				}
				
				valueOffset += mesh->GetNumVertices();
			}

			m_isIndexArrayDirty = false;
		}

		m_isIndexArrayDirty = false;
	}


	void VideoManager::Initialize()
	{
		if (m_IsInitialized)
			return;

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

		glViewport(0, 0, (int)m_windowResolution.GetX(), (int)m_windowResolution.GetY());
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		m_IsInitialized = true;
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

	int VideoManager::FindFirstIndexInBatch(Renderer* renderer)
	{
		for (unsigned int i = 0; i < m_renderers.size(); i++)
		{
			if (renderer->IsBatchEqualTo(m_renderers[i]))
				return i;
		}

		return m_renderers.size();
	}

	void VideoManager::ReserveIndexArray()
	{
		unsigned int size = 0;
		for (unsigned int i = 0; i < m_renderers.size(); i++)
			size += m_renderers[i]->GetMesh()->GetIndices()->size();

		m_indexArray.reserve(size);
	}
}