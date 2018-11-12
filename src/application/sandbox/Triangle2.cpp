#include "Triangle2.h"
#include <iostream>

namespace sb 
{
	namespace triangle2 
	{
		SDL_Window* Triangle2::m_sdlWindow;
		SDL_GLContext Triangle2::m_glContext;
		GLuint Triangle2::m_shader;

		void Triangle2::run()
		{
			createWindow();
			initOpenGl();

			bool running = true;
			while (running) {			
				// running = updateInput();
				// render();
				// flip();
			}

			close();
		}

		void Triangle2::createWindow()
		{
			int i = 42;
			#ifdef WIN32
				SDL_Init(SDL_INIT_VIDEO);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
				SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
				m_sdlWindow = SDL_CreateWindow("Sandbox", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
				m_glContext = SDL_GL_CreateContext(m_sdlWindow);
			GLenum glewError = glewInit();
			#elif defined(__ANDROID__)
				SDL_Init(SDL_INIT_VIDEO);
				SDL_DisplayMode mode;
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
				SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
				SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
				SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
				SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
				SDL_GetDisplayMode(0, 0, &mode);
				m_sdlWindow = SDL_CreateWindow("Sandbox", 0, 0, mode.w, mode.h, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
				m_glContext = SDL_GL_CreateContext(m_sdlWindow);
			#endif
		}

		void Triangle2::initOpenGl()
		{
			createShader();
		}

		void Triangle2::createShader()
		{
			m_shader = glCreateProgram();
			if (m_shader == 0)
				std::cout << "error creating shader program" << std::endl;

			std::string vertexShaderCode = getVertexShaderSource();
			std::string fragmentShaderCode = getFragmentShaderSource();
			GLuint vertexShader = (vertexShaderCode, GL_VERTEX_SHADER);
			GLuint fragmentShader = (fragmentShaderCode, GL_FRAGMENT_SHADER);

			glAttachShader(m_shader, vertexShader);
			glAttachShader(m_shader, fragmentShader);
			linkShader(m_shader);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}
	
		std::string Triangle2::getVertexShaderSource()
		{
			return
				"attribute vec2 a_vPosition;										\n"
				"attribute vec4 a_vColor;											\n"
				"varying vec4 v_vColor;												\n"
				"void main()														\n"
				"{																	\n"
				"   gl_Position = vec4(a_vPosition.x, a_vPosition.y, 0 , 1 );		\n"
				"	v_vColor = a_vColor;											\n"
				"}";
		}

		std::string Triangle2::getFragmentShaderSource()
		{
			return 
				"#version 100								\n"
					"precision mediump float;                   \n"
					"varying vec4 v_vColor;		 				\n"
					"void main()                                \n"
					"{                                          \n"
					"  gl_FragColor = v_vColor;					\n"
					"}                                          \n";
		}

		GLuint Triangle2::compileShader(std::string shaderCode, GLenum type)
		{
			GLint compiled;
			GLuint shader = glCreateShader(type);

			if (shader != 0) {
				const char* shaderCodeStr = shaderCode.c_str();
				glShaderSource(shader, 1, &shaderCodeStr, NULL);
				glCompileShader(shader);

				glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
				if (!compiled) {
					GLint infoLen = 0;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

					if (infoLen > 1) {
						char* infoLog = new char[infoLen];
						glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
						std::cout << "error compiling shader: " << infoLog << std::endl;
						delete[] infoLog;
					}
					glDeleteShader(shader);
					shader = 0;
				}
			}

			return shader;
		}

		void Triangle2::linkShader(GLuint shader)
		{
			glLinkProgram(shader);
			GLint linked;
			glGetProgramiv(shader, GL_LINK_STATUS, &linked);
			if (!linked) {
				GLint infoLen = 0;
				glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

				if (infoLen > 1) {
					char* infoLog = new char[infoLen];
					glGetProgramInfoLog(shader, infoLen, NULL, infoLog);
					std::cout << "Error linking shader program: " << std::endl << infoLog << std::endl;
					delete[] infoLog;
				}

				glDeleteProgram(shader);
			}

		}

		void Triangle2::close()
		{
			glDeleteProgram(m_shader);
			SDL_DestroyWindow(m_sdlWindow);
			SDL_Quit();
		}

	}
}

