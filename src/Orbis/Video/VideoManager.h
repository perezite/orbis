#pragma once

#include "RenderDevice.h"
#include "Texture.h"
#include "TextureAtlas.h"

#include "../Libraries/SDL.h"
using namespace Components;

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include <string>
#include <map>

namespace Video
{
	class VideoManager
	{
	public:
		// get instance
		static VideoManager* GetInstance();

		// initialize
		void Initialize(bool useDefaultResolution = true);

		// destructor
		virtual ~VideoManager();

		// clear the manager
		void Clear();

		// get the texture atlas
		TextureAtlas* GetTextureAtlas();

		// get a texture
		Texture* GetTexture(std::string assetPath, bool flipVertically = true);

		// get the resolution
		Vector2D GetResolution() { return m_windowResolution; }

		// change the window resultion
		void SetResolution(Vector2D resolution);

		// get the render device
		RenderDevice* GetRenderDevice() { return &m_renderDevice; }

		// clear the screen
		void ClearScreen();

		// swap the video buffers
		void SwapBuffers();

		// shutdown video
		void Shutdown();

	protected:
		// singleton constructor
		VideoManager();

		// get the default window resolution
		Vector2D GetDefaultWindowResolution();

		// create the sdl window
		void CreateSdlWindow();

	private:
		// the texture atlas
		TextureAtlas* m_textureAtlas;

		// the textures
		std::map<std::string, Texture*> m_textures;

		// the sdl window
		SDL_Window* m_sdlWindow;

		// the opengl context
		SDL_GLContext m_openGlContext;

		// the attached render device
		RenderDevice m_renderDevice;

		// the window resolution
		Vector2D m_windowResolution;

		// is the manager initialized
		bool m_isInitialized;

		// the default window resolution
		static const Vector2D DESKTOP_DEFAULT_RESOLUTION;
	};
}

