#include "Window.h"

#include "../Libraries/GL.h"
#include "../Core/LogUtil.h"


#include "../../Base/Base.h"
using namespace base;

#include <sstream>

namespace
{
	using namespace orb;

	void normalizeChannels(GLubyte* output_pixels, GLubyte* input_pixels, unsigned int num_pixels)
	{
		for (unsigned int i = 0; i < num_pixels; i++)
		{
			output_pixels[i * 3] = input_pixels[i * 4 + 2];
			output_pixels[i * 3 + 1] = input_pixels[i * 4 + 1];
			output_pixels[i * 3 + 2] = input_pixels[i * 4];
		}
	}

	// Reference: https://www.opengl.org/discussion_boards/showthread.php/158514-capturing-the-OpenGL-output-to-a-image-file
	// Reference: https://stackoverflow.com/questions/16538945/writing-uncompressed-tga-to-file-in-c
	// Note: For reading RGB/BGR values, you must set GL_PACK_ALIGNMENT to 1, because the default pack alignment of 4 means, 
	// that each horizontal line must be a multiple of 4 in size. If you use RGBA or ABGR, it is a multiple of 4 automatically
	// Reference: https://www.khronos.org/opengl/wiki/Common_Mistakes
	// 
	void dumpScreen()
	{
		static bool done = false;
		if (done == true)
			return;

		const int W = 10;
		const int H = 10;

		GLubyte pixels[4 * W * H];
		GLubyte normed_pixels[3 * W * H];

		// read
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(0, 0, W, H, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		auto test = glGetError();
		normalizeChannels(normed_pixels, pixels, W * H);

		// write to file
		#ifdef __WIN32__
			short  TGAhead[] = { 0, 2, 0, 0, 0, 0, W, H, 24 };
			FILE *out = fopen("D:\\Indie\\Development\\Simulo\\orbis\\bin\\Windows\\test.tga", "wb");
			fwrite(&TGAhead, sizeof(TGAhead), 1, out);
			fwrite(normed_pixels, 3 * W * H, 1, out);
			fclose(out);
		#endif

		done = true;
	}
}

namespace orb
{
	const Vector2D Window::DESKTOP_DEFAULT_RESOLUTION(400, 711);

	Window::Window()
	{
		SDL_Init(SDL_INIT_VIDEO);
		int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
		if (!IMG_Init(imgFlags) & imgFlags)
			throw Exception("epic fail");
		m_resolution = getDefaultResolution();

		#ifdef WIN32	
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			createSdlWindow();
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
			createSdlWindow();
			m_openGlContext = SDL_GL_CreateContext(m_sdlWindow);
		#endif

		glViewport(0, 0, (int)m_resolution.x, (int)m_resolution.y);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_sdlWindow);
	}

	void Window::setResolution(Vector2D resolution)
	{
		if (EnvironmentUtil::isMobile())
			return;

		SDL_DestroyWindow(m_sdlWindow);
		m_resolution = resolution;
		createSdlWindow();

		SDL_GL_MakeCurrent(m_sdlWindow, m_openGlContext);
		glViewport(0, 0, (int)m_resolution.x, (int)m_resolution.y);
	}

	void Window::clear()
	{
		glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::swapBuffers()
	{
		dumpScreen();
		SDL_GL_SwapWindow(m_sdlWindow);
	}

	Vector2D Window::getDefaultResolution()
	{
		if (EnvironmentUtil::isMobile())
		{
			SDL_DisplayMode mode;
			SDL_GetDisplayMode(0, 0, &mode);
			return Vector2D((float)mode.w, (float)mode.h);
		}

		else 
			return DESKTOP_DEFAULT_RESOLUTION;
	}

	void Window::createSdlWindow()
	{
		#ifdef WIN32
			m_sdlWindow = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)m_resolution.x, (int)m_resolution.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		#endif
		#ifdef __ANDROID__
			m_sdlWindow = SDL_CreateWindow("Example", 0, 0, (int)m_resolution.x, (int)m_resolution.y, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
		#endif
	}
}