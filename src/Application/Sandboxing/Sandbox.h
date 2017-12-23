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

		static void InitGL();

	private:
		static GLint m_positionHandle;
		static GLint m_texCoordHandle;
		static GLint m_samplerHandle;
		static GLuint m_vbo;
		static GLuint m_ibo;
		static GLuint m_texture;
	};

}
