#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include "../Libraries/SDL.h"

namespace Video
{
	class Window
	{
	public: 
		// ctor
		Window();

		// dtor
		virtual ~Window();

		// get the resolution
		Vector2D GetResolution() { return m_resolution; }

		// change the window resultion
		void SetResolution(Vector2D resolution);

		void Clear();

		// swap the video buffers
		void SwapBuffers();

	protected:		
		// get the default window resolution
		Vector2D GetDefaultResolution();

		// create the sdl window
		void CreateSdlWindow();

	private:
		// the sdl window
		SDL_Window* m_sdlWindow;

		// the opengl context
		SDL_GLContext m_openGlContext;

		// the window resolution
		Vector2D m_resolution;

		// the default window resolution
		static const Vector2D DESKTOP_DEFAULT_RESOLUTION;
	};
}