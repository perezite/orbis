#pragma once

#include <string> 
#include "OpenGL.h"

namespace orb
{
	class Shader
	{
	public:
		Shader();

	protected:
		GLuint compile(std::string shaderCode, GLenum type);

		void link(GLuint shader);

	protected:
		std::string getDefaultVertexShaderCode();

		std::string getDefaultFragmentShaderCode();

	private:
		GLuint m_shader;
	};
}