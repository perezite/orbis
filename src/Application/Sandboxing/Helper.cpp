#include "Helper.h"

#include "../../Orbis/Core/TimeManager.h"
#include "../../Orbis/Core/LogHelper.h"
using namespace Core;

namespace Sandboxing
{
	SDL_Window* Helper::m_window = NULL;
	SDL_GLContext Helper::m_context = NULL;
	GLuint Helper::m_programHandle = 0;
	std::vector<GLuint> Helper::m_textureHandles;
	long Helper::m_startTicks = 0;
	long Helper::m_numFrames = 0;
	long Helper::m_numSamples = 0;
	float Helper::m_cumulativePerformance = 0.0f;

	void Helper::Close()
	{
		glDeleteProgram(m_programHandle);
		for (unsigned int i = 0; i < m_textureHandles.size(); i++)
			glDeleteTextures(1, &m_textureHandles[i]);

		SDL_DestroyWindow(m_window);
		m_window = NULL;
		SDL_Quit();
	}

	void Helper::InitSDL()
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


	GLuint Helper::LoadShader(const char *shaderSrc, GLenum type)
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

	GLuint Helper::LoadTexture(std::string filePath, bool mirrorVertically)
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

		m_textureHandles.push_back(texture);

		return texture;
	}

	const char* Helper::GetVertexShaderCode()
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

	const char* Helper::GetFragmentShaderCode()
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

	std::string Helper::GetAssetFilePath(const char * assetPath)
	{
		std::string result(assetPath);

		#ifdef WIN32 
			result = "D:\\Indie\\Development\\Simulo\\orbis\\bin\\Assets\\" + result;
		#endif

		return result;
	}

	SDL_Surface* Helper::MirrorSurface(SDL_Surface* surface)
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

	void Helper::LogPerformance()
	{
		m_numFrames++;
		if (TimeManager::GetInstance()->GetTicks() - m_startTicks > 1000)
		{
			// track current performance
			float currentPerformance = 1000.0f / float(m_numFrames);
			LogHelper::LogMessage("%f ms/frame", currentPerformance);
			m_startTicks += 1000;
			m_numFrames = 0;

			// track average performance
			m_numSamples++;
			m_cumulativePerformance += currentPerformance;
			float average = m_cumulativePerformance / float(m_numSamples);
			LogHelper::LogMessage("Average: %f ms/frame, samples: %d", average, m_numSamples);
		}
	}
}