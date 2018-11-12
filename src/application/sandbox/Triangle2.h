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
#include <string>
#include <map>
#include <vector>

#ifdef WIN32
	#define SB_USE_VERTEX_ARRAYS 
#endif

namespace sb 
{
	namespace triangle2 
	{
		struct Vertex
		{
			float x, y;
			float r, g, b, a;
		};

		// This sandbox implements the triangle with vertex buffers and vertex arrays. Reference: https://learnopengl.com/Getting-started/Hello-Triangle
		class Triangle2
		{
		public:
			static void run();

		protected:
			static void createWindow();

			static void initOpenGl();

			static void createShader();

			static std::string getVertexShaderSource();

			static std::string getFragmentShaderSource();

			static GLuint compileShader(std::string shaderCode, GLenum type);

			static void linkShader(GLuint shader);

			static void createVertexBuffer();

			static void createVertices();

			static void updateInput();

			static void draw();

			static void flip();

			static void prepareDraw();

			static void close();

		private:
			static SDL_Window* m_sdlWindow;	

			static SDL_GLContext m_glContext;

			static bool m_running;

			static GLuint m_shader;

			static std::map<std::string, GLuint> m_attributeLocations;

			#ifdef SB_USE_VERTEX_ARRAYS
				static GLuint m_vao;
			#endif

			static GLuint m_vbo;

			static std::vector<Vertex> m_vertices;

		};
	}
}