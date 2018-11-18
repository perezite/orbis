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
				SB_GL_CHECK(glGenVertexArrays(1, &m_vao));
			#endif
			SB_GL_CHECK(glGenBuffers(1, &m_vbo));
			SB_GL_CHECK(glGenBuffers(1, &m_ibo));
		}

		GraphicsBuffers::~GraphicsBuffers()
		{
			SB_GL_CHECK(glDeleteBuffers(1, &m_ibo));
			SB_GL_CHECK(glDeleteBuffers(1, &m_vbo));

			#ifdef ORB_DESKTOP_GL
			SB_GL_CHECK(glDeleteVertexArrays(1, &m_vao));
			#endif
		}
	
		void GraphicsBuffers::bindVertexBuffer()
		{
			SB_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		}

		void GraphicsBuffers::bindIndexBuffer()
		{
			SB_GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
		}

		void GraphicsBuffers::setVertexData(GLsizeiptr size, const GLvoid* data, GLenum usage)
		{
			SB_GL_CHECK(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
		}

		void GraphicsBuffers::setVertexSubData(GLsizeiptr offset, GLsizeiptr size, const GLvoid* data)
		{
			SB_GL_CHECK(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
		}

		void GraphicsBuffers::setIndexData(GLsizeiptr size, const GLvoid* data, GLenum usage)
		{
			SB_GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
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
			SB_GL_CHECK(glBindVertexArray(m_vao));
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

				SB_GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));	// when using a vao, the binding of the index buffer must be recorded when the vao is bound, which
																			// is at this point. Failure to do so will result in the vao resetting all previously bound index buffers
																			// when being bound
			}

		#endif

		void GraphicsBuffers::update()
		{
			SB_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
			for(std::map<GLuint, VertexAttribPointer>::iterator it = m_vertexAttribPointers.begin(); it != m_vertexAttribPointers.end(); ++it)
			{
				GLuint index = it->first;
				VertexAttribPointer vap = it->second;
				SB_GL_CHECK(glEnableVertexAttribArray(index));
				SB_GL_CHECK(glVertexAttribPointer(index, vap.size, vap.type, vap.normalized, vap.stride, vap.pointer));
			}

			SB_GL_CHECK(glEnableVertexAttribArray(0));
			SB_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}
	}
}

