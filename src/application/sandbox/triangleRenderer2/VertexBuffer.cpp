#include "VertexBuffer.h"

namespace sb
{
	namespace triangleRenderer2
	{
		void VertexBuffer::init()
		{
			#ifdef ORB_GL
				glGenVertexArrays(1, &m_vao);
			#endif
			glGenBuffers(1, &m_vbo);
		}

		VertexBuffer::~VertexBuffer()
		{
			glDeleteBuffers(1, &m_vbo);

			#ifdef ORB_GL
				glDeleteVertexArrays(1, &m_vao);
			#endif
		}
	
		void VertexBuffer::bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		}

		void VertexBuffer::unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VertexBuffer::setData(GLsizeiptr size, const GLvoid* data, GLenum usage)
		{
			glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		}

		void VertexBuffer::setSubData(GLsizeiptr offset, GLsizeiptr size, const GLvoid* data)
		{
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		}

		void VertexBuffer::setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* pointer)
		{
			m_vertexAttribPointers[index] = VertexAttribPointer{ size, type, normalized, stride, pointer };
		}

		void VertexBuffer::enable()
		{
			#ifdef ORB_GL
				glBindVertexArray(m_vao);
				if (m_isVaoInitialised == false) {
					setupVertexAttribPointers();
					m_isVaoInitialised = true;
				}
			#else
				setupVertexAttribPointers();
			#endif		
		}

		void VertexBuffer::setupVertexAttribPointers()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			for(std::map<GLuint, VertexAttribPointer>::iterator it = m_vertexAttribPointers.begin(); it != m_vertexAttribPointers.end(); ++it)
			{
				GLuint index = it->first;
				VertexAttribPointer vap = it->second;
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(index, vap.size, vap.type, vap.normalized, vap.stride, vap.pointer);
			}
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}
