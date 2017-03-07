#pragma once

#include "Color.h"

#include "..\..\Base\Math\Vector2D.h"
using namespace Math;

#define NO_SDL_GLEXT
#include <SDL_opengl.h>
#include <SDL.h>

namespace Video
{
	enum RenderMode
	{
		Lines = GL_LINES,
		LineStrip = GL_LINE_STRIP,
		LineLoop = GL_LINE_LOOP,
		Quads = GL_QUADS,
		Polygon = GL_POLYGON,
		ConcavePolygon
	};

	enum MatrixMode
	{
		Modelview = GL_MODELVIEW,
		Projection = GL_PROJECTION,
		Texturing = GL_TEXTURE,
		Colour = GL_COLOR
	};

	// wraps low-level graphics calls within a single static class
	class GraphicsAdapter
	{
	public: 
		// set matrix mode
		static void SetMatrixMode(MatrixMode matrixMode);

		// safe load identity matrix
		static void SafeLoadIdentityMatrix();

		// load identity matrix
		static void LoadIdentityMatrix();

		// apply global translation
		static void ApplyGlobalTranslation(Vector2D translation);

		// apply global scale
		static void ApplyGlobalScale(Vector2D scale);

		// apply global rotation
		static void ApplyGlobalRotation(float rotation);

		// safe set clear color
		static void SafeSetClearColor(Color color);

		// set clear color
		static void SetClearColor(Color color);

		// clear screen
		static void ClearScreen();

		// begin primitive
		static void BeginPrimitive(RenderMode renderMode);

		// set vertex 2D
		static void SetVertex2D(Vector2D position);

		// end primitive
		static void EndPrimitive();

		// Initialize graphics
		static void InitializeGraphics(int windowWidth, int windowHeight);

		// Quit graphics
		static void QuitGraphics();

		// Swap graphics buffers
		static void SwapBuffers();

		// assert that no error happened
		static void AssertNoError();
	protected: 
		// initialize SDL video subsystem
		static void InitializeSDLVideoSubsystem();

		// Create window
		static void CreateSDLWindow(int windowWidth, int windowHeight);

		// Destroy window
		static void DestroySDLWindow();

		// Create openGL context
		static void CreateOpenGLContext();

		// Set OpenGL swap interval
		static void SetOpenGLSwapInterval(int interval);

	private:
		// SDL window
		static SDL_Window *m_SDLWindow;

		// SDL to OpenGL context
		static SDL_GLContext m_OpenGLContext;

		// OpenGL Major Version number
		static const int OpenGLContextMajorVersion = 2;

		// OpenGL Minor version number
		static const int OpenGLContextMinorVersion = 1;
	};
}