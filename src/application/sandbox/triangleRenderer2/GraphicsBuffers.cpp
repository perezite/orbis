#include "GraphicsBuffers.h"

namespace sb
{
	namespace triangleRenderer2
	{
		bool operator==(const VertexAttribPointer& left, const VertexAttribPointer& right) {
			return
				left.size == right.size && left.type == right.type && left.normalized == right.normalized && left.stride == right.stride && left.pointer == right.pointer;
		}

		bool operator!=(const VertexAttribPointer& left, const VertexAttribPointer& right) {
			return !(left == right);
		}

		void GraphicsBuffers::init()
		{
			#ifdef ORB_DESKTOP_GL
				glGenVertexArrays(1, &m_vao);
			#endif
			glGenBuffers(1, &m_vbo);
			glGenBuffers(1, &m_ibo);
		}

		GraphicsBuffers::~GraphicsBuffers()
		{
			glDeleteBuffers(1, &m_ibo);
			glDeleteBuffers(1, &m_vbo);

			#ifdef ORB_DESKTOP_GL
				glDeleteVertexArrays(1, &m_vao);
			#endif
		}
	
		void GraphicsBuffers::bindVertexBuffer()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		}

		void GraphicsBuffers::bindIndexBuffer()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		}

		void GraphicsBuffers::setVertexData(GLsizeiptr size, const GLvoid* data, GLenum usage)
		{
			glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		}

		void GraphicsBuffers::setVertexSubData(GLsizeiptr offset, GLsizeiptr size, const GLvoid* data)
		{
			glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
		}

		void GraphicsBuffers::setIndexData(GLsizeiptr size, const GLvoid* data, GLenum usage)
		{
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
		}

		void GraphicsBuffers::setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid* pointer)
		{
			VertexAttribPointer vap = VertexAttribPointer{ size, type, normalized, stride, pointer };
			if (m_vertexAttribPointers.find(index) == m_vertexAttribPointers.end() || m_vertexAttribPointers[index] != vap)
				m_vaoNeedsUpdate = true;

			m_vertexAttribPointers[index] = vap;
		}

		void GraphicsBuffers::enable()
		{
			#ifdef ORB_DESKTOP_GL
				glBindVertexArray(m_vao);
				if (m_vaoNeedsUpdate) {
					updateVao();
					m_vaoNeedsUpdate = false;
				}
			#else
				update();
			#endif	
		}

		#ifdef ORB_DESKTOP_GL

			void GraphicsBuffers::updateVao()
			{
				update();

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);	// we record the correct index buffer binding in the VAO. Otherwise binding the VAO will cause a default 
																// binding (i.e. NO binding) for the index buffer, which is not what we want for subsequent glDrawElement calls

			}

		#endif

		void GraphicsBuffers::update()
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

