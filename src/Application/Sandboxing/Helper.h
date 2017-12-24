#pragma once

#include "../../Orbis/Libraries/GL.h"
#include "../../Orbis/Libraries/SDL.h"

#include <vector>

namespace Sandboxing
{
	class Helper
	{
	public:
		static void SetStartTicks(long startTicks) { m_startTicks = startTicks; }

		static void SetNumFrames(long numFrames) { m_numFrames = numFrames; }

		static SDL_Window* GetWindow() { return m_window; }

		static GLuint GetShaderProgramHandle() { return m_programHandle; }

		static GLuint CreateShaderProgram() { return m_programHandle = glCreateProgram(); }

		static void Close();

		static void InitSDL();

		static GLuint LoadShader(const char *shaderSrc, GLenum type);

		static GLuint LoadTexture(std::string filePath, bool flipVertically = false);

		static const char* GetFragmentShaderCode();

		static const char* GetVertexShaderCode();

		static std::string GetAssetFilePath(const char* assetPath);

		static void LogPerformance();

	protected:
		static SDL_Surface* MirrorSurface(SDL_Surface* surface);

	private:
		static SDL_Window* m_window;
		static SDL_GLContext m_context;
		static GLuint m_programHandle;
		static std::vector<GLuint> m_textureHandles;
		static long m_startTicks;
		static long m_numFrames;
		static long m_numSamples;
		static float m_cumulativePerformance;
	};
}