#include "Sandbox.h"

#ifdef __SANDBOX__

#include "../../Orbis/Core/LogHelper.h"
using namespace Core;

#include <stdio.h>
#include <string>
#include <iostream>

namespace Sandboxing
{
	SDL_Window* Sandbox::m_window = NULL;
	SDL_GLContext Sandbox::m_context = NULL;
	GLuint Sandbox::m_programHandle = 0;
	GLint Sandbox::m_positionHandle = -1;
	GLint Sandbox::m_texCoordHandle = -1;
	GLint Sandbox::m_samplerHandle = -1;
	GLuint Sandbox::m_vbo = 0;
	GLuint Sandbox::m_ibo = 0;
	GLuint Sandbox::m_texture = 0;

	void Sandbox::Run()
	{
		InitSDL();
		InitGL();

		bool quit = false;

		SDL_Event e;

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN || e.type == SDL_FINGERDOWN)
				{
					quit = true;
				}
			}

			Render();

			SDL_GL_SwapWindow(m_window);
		}

		Close();
	}

	void Sandbox::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(m_programHandle);

		glEnableVertexAttribArray(m_positionHandle);
		glEnableVertexAttribArray(m_texCoordHandle);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture(GL_TEXTURE_2D, m_texture);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(m_samplerHandle, 0);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glVertexAttribPointer(m_positionHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
		glVertexAttribPointer(m_texCoordHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)(0 + 2 * sizeof(GL_FLOAT)));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		glDisableVertexAttribArray(m_texCoordHandle);
		glDisableVertexAttribArray(m_positionHandle);
		glDisable(GL_TEXTURE_2D);
		glUseProgram(0);
	}

	void Sandbox::Close()
	{
		glDeleteProgram(m_programHandle);

		SDL_DestroyWindow(m_window);
		m_window = NULL;

		SDL_Quit();
	}

	void Sandbox::InitSDL()
	{
		#ifdef WIN32
			SDL_Init(SDL_INIT_VIDEO);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			m_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
			m_context = SDL_GL_CreateContext(m_window);
			GLenum glewError = glewInit();
		#endif
		#ifdef __ANDROID__
			SDL_Init(SDL_INIT_VIDEO);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			SDL_DisplayMode mode;
			SDL_GetDisplayMode(0, 0, &mode);
			m_window = SDL_CreateWindow(NULL, 0, 0, mode.w, mode.h, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
			m_context = SDL_GL_CreateContext(m_window);
		#endif
	}

	void Sandbox::InitGL()
	{
		m_programHandle = glCreateProgram();

		GLuint vertexShader = LoadShader(GetVertexShaderCode(), GL_VERTEX_SHADER);
		glAttachShader(m_programHandle, vertexShader);

		GLuint fragmentShader = LoadShader(GetFragmentShaderCode(), GL_FRAGMENT_SHADER);
		glAttachShader(m_programHandle, fragmentShader);

		glLinkProgram(m_programHandle);
		glUseProgram(m_programHandle);

		m_positionHandle = glGetAttribLocation(m_programHandle, "a_vPosition");
		m_texCoordHandle = glGetAttribLocation(m_programHandle, "a_texCoord");
		m_samplerHandle = glGetUniformLocation(m_programHandle, "s_texture");

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		GLfloat vertexData[] =
		{
			-0.5f, -0.5f,	// left bottom pos
			0.0f,  0.0f,	// left bottom tex
			0.5f, -0.5f,	// right bottom pos
			1.0f,  0.0f,	// right bottom tex
			-0.5f,  0.5f,	// left top pos pos
			0.0f,  1.0f,	// left top tex
			0.5f,  0.5f,	// right top pos
			1.0f,  1.0f		// right top tex
		};

		GLuint indexData[] = { 0, 1, 2, 2, 1, 3 };

		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, 2 * 8 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

		m_texture = LoadTexture(GetAssetFilePath("Textures/YellowBlock.png"), true);
	}

	GLuint Sandbox::LoadShader(const char *shaderSrc, GLenum type)
	{
		GLuint shader;
		GLint compiled;

		// Create the shader object
		shader = glCreateShader(type);
		if (shader != 0)
		{
			// Load the shader source
			glShaderSource(shader, 1, &shaderSrc, NULL);

			// Compile the shader
			glCompileShader(shader);
			// Check the compile status
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

			if (!compiled)
			{
				GLint infoLen = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

				if (infoLen > 1)
				{
					char* infoLog = new char[infoLen];
					glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
					LogHelper::ShowMessageBox(infoLog, "Shader error");
					delete[] infoLog;
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}
		return shader;
	}

	int Sandbox::LoadTexture(std::string filePath, bool mirrorVertically)
	{
		SDL_Surface* img = IMG_Load(filePath.c_str());
		SDL_Surface* img2 = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_ABGR8888, SDL_SWSURFACE);
		SDL_FreeSurface(img);
		img = img2;

		if (mirrorVertically)
		{
			SDL_Surface* flipped = MirrorSurface(img);
			SDL_FreeSurface(img);
			img = flipped;
		}

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
		SDL_FreeSurface(img);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		return texture;
	}

	SDL_Surface* Sandbox::MirrorSurface(SDL_Surface* surface)
	{
		SDL_Surface *flipped = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
			surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

		// lock
		if (SDL_MUSTLOCK(surface))
			SDL_LockSurface(surface);
		if (SDL_MUSTLOCK(flipped))
			SDL_LockSurface(flipped);

		// copy flipped
		for (int row = surface->h - 1; row >= 0; row--)
		{
			for (int col = 0; col < surface->w; col++)
			{
				size_t sourceOffset = row * surface->w + col;
				size_t sourceOffsetBytes = sourceOffset * surface->format->BytesPerPixel;
				size_t destOffset = (surface->h - row - 1) * surface->w + col;
				size_t destOffsetBytes = destOffset * surface->format->BytesPerPixel;

				memcpy((char*)flipped->pixels + destOffsetBytes, (char*)surface->pixels + sourceOffsetBytes, surface->format->BytesPerPixel);
			}
		}

		// unlock
		if (SDL_MUSTLOCK(flipped))
			SDL_UnlockSurface(flipped);
		if (SDL_MUSTLOCK(surface))
			SDL_UnlockSurface(surface);

		return flipped;
	}

	const char* Sandbox::GetVertexShaderCode()
	{
		return
			"attribute vec2 a_vPosition;	\n \
			attribute vec2 a_texCoord;		\n \
			varying vec2 v_texCoord;		\n \
											\n \
			void main()						\n \
			{								\n \
				gl_Position = vec4( a_vPosition.x, a_vPosition.y, 0, 1 ); \n \
				v_texCoord = a_texCoord;		\n \
			}";
	}

	const char* Sandbox::GetFragmentShaderCode()
	{
		return
			"#version 100					\n \
			precision highp float;			\n \
			varying vec2 v_texCoord;		\n \
			uniform sampler2D s_texture;	\n \
											\n \
			void main()						\n \
			{								\n \
				gl_FragColor = texture2D(s_texture, v_texCoord);  \n \
			}";
	}

	std::string Sandbox::GetAssetFilePath(const char * assetPath)
	{
		std::string result(assetPath);

		#ifdef WIN32 
			result = "D:\\Indie\\Development\\Simulo\\orbis\\bin\\Assets\\" + result;
		#endif

		return result;
	}
}

#endif // __SANDBOX__