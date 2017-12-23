#define __SANDBOX__

#include "../../Orbis/Libraries/GL.h"
#include "../../Orbis/Libraries/SDL.h"

#include <string>
#include <vector>

namespace Sandboxing
{
	class Sandbox
	{
	public:
		static void Run();

	protected:
		static void Render();

		static void InitGL();

		static void UpdateVertexArray();
	private:
		static GLint m_positionHandle;
		static GLint m_texCoordHandle;
		static GLint m_samplerHandle;
		static GLuint m_texture;
		static std::vector<GLfloat> m_vertices;
		static std::vector<GLushort> m_indices;
	};

}
