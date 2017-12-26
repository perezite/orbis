#pragma once

#include "RenderDevice.h"

#include "../Libraries/SDL.h"
#include "../Components/Renderer.h"
using namespace Components;

#include "../../Base/Math/Vector2D.h"
using namespace Math;

namespace Video
{
	class VideoManager
	{
	public:
		// get instance
		static VideoManager* GetInstance();

		// initialize
		void Initialize();

		// destructor
		virtual ~VideoManager();

		// get the resolution
		Vector2D GetResolution() { return m_windowResolution; }

		// get the render device
		RenderDevice* GetRenderDevice() const { return m_renderDevice; }

		// get the vertex array
		std::vector<GLfloat>& GetVertexArray() { return m_vertexArray; }

		// get the index array
		std::vector<GLushort>& GetIndexArray() { return m_indexArray; }

		// get the renderers
		std::vector<Renderer*>& GetRenderers() { return m_renderers; }

		// add a renderer
		void AddRenderer(Renderer* renderer);

		// clear the screen
		void ClearScreen();

		// swap the video buffers
		void SwapBuffers();

		// insert renderers indices at position in index array
		void UpdateIndexArray();

	protected:
		// singleton constructor
		VideoManager();

		// get the default window resolution
		Vector2D GetDefaultWindowResolution();

		// find index of last renderer in render batch
		int FindFirstIndexInBatch(Renderer* renderer);

		// reserve index array space
		void ReserveIndexArray();
	private:
		// the vertex array
		std::vector<GLfloat> m_vertexArray;

		// the index array
		std::vector<GLushort> m_indexArray;

		// is the index array in dirty state
		bool m_isIndexArrayDirty;

		// the renderer components
		std::vector<Renderer*> m_renderers;

		// the sdl window
		SDL_Window* m_sdlWindow;

		// the opengl context
		SDL_GLContext m_openGlContext;

		// the attached render device
		RenderDevice* m_renderDevice;

		// the window resolution
		Vector2D m_windowResolution;

		// the default window resolution
		static const Vector2D m_DefaultWindowResolution;

		// is the manager initialized
		bool m_IsInitialized;
	};
}

