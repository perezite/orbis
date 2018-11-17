#pragma once

#ifdef  WIN32
	#include <gl/glew.h>
	#include <SDL2/SDL_opengl.h>
	#include <gl/glu.h>
	#define ORB_DESKTOP_GL
#else
	#include <GLES2/gl2.h>	
	#include <GLES2/gl2ext.h>
	#define ORB_EMBEDDED_GL
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

		bool operator==(const VertexAttribPointer& left, const VertexAttribPointer& right);
		bool operator!=(const VertexAttribPointer& left, const VertexAttribPointer& right);

		class GraphicsBuffers
		{
		public:
			GraphicsBuffers() : m_vbo(0), m_ibo(0)
			{ }

			virtual ~GraphicsBuffers();

			void init();

			void bindVertexBuffer();

			void bindIndexBuffer();

			void setVertexData(GLsizeiptr size, const GLvoid* data, GLenum usage);

			void setVertexSubData(GLsizeiptr offset, GLsizeiptr size, const GLvoid* data);

			void setIndexData(GLsizeiptr size, const GLvoid* data, GLenum usage);

			void setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* pointer);

			void enable();

		protected:
			#ifdef ORB_DESKTOP_GL
				void updateVao();
			#endif

			void update();

		private:
			#ifdef ORB_DESKTOP_GL
				GLuint m_vao;
			#endif	

			bool m_vaoNeedsUpdate;

			GLuint m_vbo;

			GLuint m_ibo;

			std::map<GLuint, VertexAttribPointer> m_vertexAttribPointers;
		};
	}
}