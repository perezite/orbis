#include "Triangle2.h"
#include <iostream>

namespace sb 
{
	namespace triangle2 
	{
		SDL_Window* Triangle2::m_sdlWindow;
		SDL_GLContext Triangle2::m_glContext;
		bool Triangle2::m_running = true;
		GLuint Triangle2::m_shader;
		std::map<std::string, GLuint> Triangle2::m_attributeLocations;
		GLuint Triangle2::m_vao;
		GLuint Triangle2::m_vbo;
		std::vector<Vertex> Triangle2::m_vertices;

		void Triangle2::run()
		{
			createWindow();
			initOpenGl();

			while (m_running) {			
				updateInput();
				draw();
				flip();
			}

			close();
		}

		void Triangle2::createWindow()
		{
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

			m_attributeLocations["a_vPosition"] = glGetAttribLocation(m_shader, "a_vPosition");
			m_attributeLocations["a_vColor"] = glGetAttribLocation(m_shader, "a_vColor");

			createVertices();
			createVertexInput();
		}

		void Triangle2::createShader()
		{
			m_shader = glCreateProgram();
			if (m_shader == 0) {
				std::cout << "error creating shader program" << std::endl;
				std::cin.get();
			}

			std::string vertexShaderCode = getVertexShaderSource();
			std::string fragmentShaderCode = getFragmentShaderSource();
			GLuint vertexShader = compileShader(vertexShaderCode, GL_VERTEX_SHADER);
			GLuint fragmentShader = compileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);

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
				"#version 100										\n"
					"precision mediump float;						\n"
					"varying vec4 v_vColor;		 					\n"
					"void main()									\n"
					"{												\n"
					"  gl_FragColor = v_vColor;						\n"
					"}												\n";
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
						std::cin.get();
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
					std::cin.get();
					delete[] infoLog;
				}

				glDeleteProgram(shader);
			}
		}

		void Triangle2::createVertexInput()
		{
			#ifdef WIN32

				glGenVertexArrays(1, &m_vao); 
				glGenBuffers(1, &m_vbo);

				glBindVertexArray(m_vao);
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

				glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &(m_vertices.data()[0]), GL_STATIC_DRAW);
				glEnableVertexAttribArray(m_attributeLocations["a_vPosition"]);
				glEnableVertexAttribArray(m_attributeLocations["a_vColor"]);
				glVertexAttribPointer(m_attributeLocations["a_vPosition"], 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);	// Vertex attributes stay the same
				glVertexAttribPointer(m_attributeLocations["a_vColor"], 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(float)));	// Vertex attributes stay the same
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, NULL);
				glBindVertexArray(NULL);

			#elif defined(__ANDROID__)

				glGenBuffers(1, &m_vbo);
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &(m_vertices.data()[0]), GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

			#else		
				#error Platform not supported
			#endif				
		}

		void Triangle2::createVertices()
		{
			m_vertices = {  Vertex { -1, -1, 1, 0, 0, 1 },
							Vertex {  1, -1, 0, 1, 0, 1 },
							Vertex {  0,  1, 0, 0, 1, 1 } };
		}

		void Triangle2::updateInput()
		{
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT)
					m_running = false;
			}
		}

		void Triangle2::draw()
		{
			prepareDraw();

			glDrawArrays(GL_TRIANGLES, 0, 3);

			GLuint error = glGetError();
			if (error != 0) {
				std::cout << error << std::endl;
				std::cin.get();
			}
		}

		void Triangle2::flip()
		{
			SDL_GL_SwapWindow(m_sdlWindow);
		}

		void Triangle2::prepareDraw()
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(m_shader);

			prepareVertexInput();		

		}

		void Triangle2::prepareVertexInput()
		{
			#ifdef WIN32

				glBindVertexArray(m_vao);

			#elif defined(__ANDROID__)

				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
				auto test1 = m_attributeLocations["a_vPosition"];
				auto test2 = m_attributeLocations["a_vColor"];
				glEnableVertexAttribArray(m_attributeLocations["a_vPosition"]);
				glEnableVertexAttribArray(m_attributeLocations["a_vColor"]);
				glVertexAttribPointer(m_attributeLocations["a_vPosition"], 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);	// Vertex attributes stay the same
				glVertexAttribPointer(m_attributeLocations["a_vColor"], 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(float)));	// Vertex attributes stay the same
				glEnableVertexAttribArray(0);

			#else
				#error Platform not supported
			#endif

		}

		void Triangle2::close()
		{
			glDeleteProgram(m_shader);
			SDL_DestroyWindow(m_sdlWindow);
			SDL_Quit();
		}

	}
}

