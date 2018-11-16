#include "Triangle2.h"
#include <iostream>
#include <stddef.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <chrono>

namespace sb 
{
	namespace triangle2 
	{
		SDL_Window* Triangle2::m_sdlWindow;
		SDL_GLContext Triangle2::m_glContext;
		bool Triangle2::m_running = true;
		GLuint Triangle2::m_shader;
		std::map<std::string, GLuint> Triangle2::m_attributeLocations;
		VertexBuffer Triangle2::m_vertexBuffer;
		std::vector<Vertex> Triangle2::m_vertices;
		std::vector<Vertex> Triangle2::m_transformedVertices;
		std::vector<Transform> Triangle2::m_transforms;

		void Triangle2::run()
		{
			createWindow();
			initOpenGl();
			initVertices();

			while (m_running) {			
				updateInput();
				draw();
				display();
				SDL_GL_SwapWindow(m_sdlWindow);
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

			m_vertexBuffer.init();
		}

		void Triangle2::initVertices()
		{
			m_vertices = {	Vertex{ Vector2f{ -0.5f,		-0.5f },		Color{ 1, 0, 0, 1 } },
							Vertex{ Vector2f{ 0,		-0.5f },		Color{ 0, 1, 0, 1 } },
							Vertex{ Vector2f{ -0.25f,	 0 },		Color{ 0, 0, 1, 1 } },
							Vertex{ Vector2f{ 0.5f,      0.5f },		Color{ 1, 0, 0, 1 } },
							Vertex{ Vector2f{ 0,		 0.5f },		Color{ 0, 1, 0, 1 } },
							Vertex{ Vector2f{ 0.25f,	 0 },		Color{ 0, 0, 1, 1 } } };
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
			// drawVersion1();
			// drawVersion2();
			drawVersion3();
		}

		void Triangle2::drawVersion1()
		{
			computeTransformedVertices();
			m_vertexBuffer.bind();
			m_vertexBuffer.setData(m_vertices.size() * sizeof(Vertex), &(m_transformedVertices[0]), GL_DYNAMIC_DRAW);		
		}

		void Triangle2::drawVersion2() 
		{
			computeTransformedVertices();
			m_vertexBuffer.bind();
			m_vertexBuffer.setData(m_vertices.size() * sizeof(Vertex), NULL, GL_STREAM_DRAW);		// buffer orphaning
			m_vertexBuffer.setSubData(0, m_vertices.size() * sizeof(Vertex), &(m_transformedVertices[0]));
		}

		void Triangle2::drawVersion3()
		{
			computeTransformedVertices();
			m_vertexBuffer.bind();
			m_vertexBuffer.setData(m_vertices.size() * sizeof(Vertex), NULL, GL_STREAM_DRAW);		// buffer orphaning
			for (unsigned int i = 0; i < m_vertices.size(); i++)									// buffer sub-updates
				m_vertexBuffer.setSubData(i * sizeof(Vertex) + offsetof(Vertex, position), sizeof(Vertex), &(m_transformedVertices[i].position));
		}

		void Triangle2::computeTransformedVertices()
		{
			static float alpha = 0;
			const float omega = 1.5f;
			alpha = fmod(alpha + getElapsedTime() * omega, 2 * (float)M_PI);
			float ca = cosf(alpha), sa = sinf(alpha);
			
			m_transformedVertices.resize(m_vertices.size());
			for (std::size_t i = 0; i < m_vertices.size(); i++) {
				bool ccw = (i % 6) < 3;
 				Vector2f pos = m_vertices[i].position;
				if (ccw)
					m_transformedVertices[i].position = Vector2f{ ca * pos.x - sa * pos.y,  sa * pos.x + ca * pos.y };
				else
					m_transformedVertices[i].position = Vector2f{ ca * pos.x + sa * pos.y, -sa * pos.x + ca * pos.y };
				m_transformedVertices[i].color = m_vertices[i].color;
			}
		}
	
		float Triangle2::getElapsedTime() {
			static clock_t current = clock();
			clock_t last = current;
			current = clock();
			return 
			#ifdef __ANDROID__
				(float(current - last) / CLOCKS_PER_SEC) * 100.0f;			// better don't ask...
			#else
				float(current - last) / CLOCKS_PER_SEC;
			#endif	
		}

		void Triangle2::display()
		{
			prepareDisplay();

			glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

			GLuint error = glGetError();
			if (error != 0) {
				std::cout << error << std::endl;
				std::cin.get();
			}
		}

		void Triangle2::prepareDisplay()
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			glUseProgram(m_shader);

			m_vertexBuffer.setVertexAttribPointer(m_attributeLocations["a_vPosition"], 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			m_vertexBuffer.setVertexAttribPointer(m_attributeLocations["a_vColor"], 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
			m_vertexBuffer.enable();
		}

		void Triangle2::close()
		{
			glDeleteProgram(m_shader);
			SDL_DestroyWindow(m_sdlWindow);
			SDL_Quit();
		}


	}
}

