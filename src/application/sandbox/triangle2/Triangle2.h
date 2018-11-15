#pragma once

#include "VertexBuffer.h"
#include "Vector2f.h"
#include "Color.h"

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

namespace sb 
{
	namespace triangle2 
	{
		struct Vertex
		{
			Vector2f position;
			Color color;
		};

		// This sandbox implements the triangle with vertex buffers and vertex array objects. 
		// References:	https://learnopengl.com/Getting-started/Hello-Triangle
		//				https://www.youtube.com/watch?v=ImtWD_9OAeY&t=2s
		//				http://www.learnopengles.com/android-lesson-seven-an-introduction-to-vertex-buffer-objects-vbos/
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

			static void createVertices();

			static void updateInput();

			static void draw();

			static void drawVersion1();

			static void drawVersion2();

			static void drawVersion3();

			static void computeTransformedVertices();

			static float getElapsedTime();

			static void display();

			static void prepareDisplay();

			static void close();

		private:
			static SDL_Window* m_sdlWindow;	

			static SDL_GLContext m_glContext;

			static bool m_running;

			static GLuint m_shader;

			static std::map<std::string, GLuint> m_attributeLocations;

			static VertexBuffer m_vertexBuffer;

			static std::vector<Vertex> m_vertices;

			static std::vector<Vertex> m_transformedVertices;

		};
	}
}