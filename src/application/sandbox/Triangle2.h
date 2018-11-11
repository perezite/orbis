#pragma once

#ifdef  WIN32
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#else
#include <GLES2/gl2.h>	
#include <GLES2/gl2ext.h>
#endif 
#include <SDL2/SDL.h>

namespace sb 
{
	namespace triangle2 
	{
		// This sandbox implements the triangle with vertex buffers and vertex arrays. Reference: https://learnopengl.com/Getting-started/Hello-Triangle
		class Triangle2
		{
		public:
			static void run();

		protected:
			static void createWindow();

			static void close();

		private:
			static SDL_Window* m_sdlWindow;	

			static SDL_GLContext m_glContext;

		};
	}
}