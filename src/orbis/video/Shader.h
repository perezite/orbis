#pragma once
 
#include "OpenGL.h"
#include <string>
#include <map>

namespace orb
{
	class Shader
	{
	public:
		Shader();

		void setAttributePointer(std::string attributeName, GLvoid* pointer, GLint numVerticesPerElement, GLsizei stride, GLenum elementType);

		void use();

		void unuse();

	protected:
		GLuint compile(std::string shaderCode, GLenum type);

		void link(GLuint shader);

	protected:
		std::string getDefaultVertexShaderCode();

		std::string getDefaultFragmentShaderCode();

	private:
		GLuint m_shader;

		std::map<std::string, GLuint> m_attributeLocations;
	};
}