#define __SANDBOX__

#include "../../Orbis/Libraries/GL.h"
#include "../../Orbis/Libraries/SDL.h"

#include <string>

namespace Sandboxing
{
	class Sandbox
	{
	public:
		static void Run();

	protected:
		static void Render();

		static void Close();

		static void InitSDL();

		static void InitGL();

		static GLuint LoadShader(const char *shaderSrc, GLenum type);

		static int LoadTexture(std::string filePath, bool flipVertically = false);

		static SDL_Surface* MirrorSurface(SDL_Surface* surface);

		static const char* GetFragmentShaderCode();

		static const char* GetVertexShaderCode();

		static std::string GetAssetFilePath(const char* assetPath);

	private:
		static SDL_Window* m_window;
		static SDL_GLContext m_context;
		static GLuint m_programHandle;
		static GLint m_positionHandle;
		static GLint m_texCoordHandle;
		static GLint m_samplerHandle;
		static GLuint m_vbo;
		static GLuint m_ibo;
		static GLuint m_texture;
	};

}
