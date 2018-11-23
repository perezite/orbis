#pragma once

#ifdef  WIN32
	#include <gl/glew.h>
	#include <SDL2/SDL_opengl.h>
	#include <gl/glu.h>
	#define ORB_GL
#else
	#include <GLES2/gl2.h>	
	#include <GLES2/gl2ext.h>
	#define ORB_GLES
#endif 

#include <map>

namespace sb
{
	namespace triangleRenderer2
	{
		struct VertexAttribPointer
		{
			GLint size; GLenum type; GLboolean normalized; GLsizei stride; GLvoid* pointer;
		};

		class GraphicsBuffer
		{
		public:
			virtual ~GraphicsBuffer();

			void init();

			void bind();

			void unbind();

			void setData(GLsizeiptr size, const GLvoid* data, GLenum usage);

			void setSubData(GLsizeiptr offset, GLsizeiptr size, const GLvoid* data);

			void setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* pointer);

			void enable();

		protected:
			void setupVertexAttribPointers();

		private:
			#ifdef ORB_GL
				GLuint m_vao;

				bool m_isVaoInitialised;
			#endif	

			GLuint m_vbo;

			std::map<GLuint, VertexAttribPointer> m_vertexAttribPointers;
		};
	}
}