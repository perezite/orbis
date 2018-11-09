#include "Shader.h"
#include "../core/Error.h"

namespace orb
{
	Shader::Shader()
	{
		GLuint vertexShader = compile(getDefaultVertexShaderCode(), GL_VERTEX_SHADER);
		GLuint fragmentShader = compile(getDefaultFragmentShaderCode(), GL_FRAGMENT_SHADER);

		GLuint m_shader = glCreateProgram();
		if (m_shader == 0)
			ORB_ERROR() << "error creating shader program";
		
		glAttachShader(m_shader, vertexShader);
		glAttachShader(m_shader, fragmentShader);
		link(m_shader);
	}

	GLuint Shader::compile(std::string shaderCode, GLenum type)
	{
		GLint compiled;
		GLuint shader = glCreateShader(type);

		if (shader != 0) {
			const char* shaderCodeStr = shaderCode.c_str();
			glShaderSource(shader, 1, &shaderCodeStr, NULL);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled) {
				GLint infoLen = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

				if (infoLen > 1) {
					char* infoLog = new char[infoLen];
					glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
					ORB_ERROR() << "shader compilation failed: " << infoLog << std::endl;
					delete[] infoLog;
				}
				glDeleteShader(shader);
				shader = 0;
			}
		}

		return shader;
	}

	void Shader::link(GLuint shader)
	{
		glLinkProgram(shader);

		GLint linked;
		glGetProgramiv(shader, GL_LINK_STATUS, &linked);
		if (!linked) {
			GLint infoLen = 0;
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1) {
				char* infoLog = new char[infoLen];
				glGetProgramInfoLog(shader, infoLen, NULL, infoLog);
				ORB_ERROR() << "Error linking shader program: " << std::endl << infoLog << std::endl;
				delete[] infoLog;
			}

			glDeleteProgram(shader);
		}
	}

	std::string Shader::getDefaultVertexShaderCode()
	{
		return
			"attribute vec2 a_vPosition;										\n"
			"attribute vec4 a_vColor;											\n"
			"varying vec4 v_vColor;												\n"
			"void main()														\n"
			"{																	\n"
			"   gl_Position = vec4(a_vPosition.x, a_vPosition.y, 0 , 1 );		\n"
			"	v_vColor = a_vColor;											\n"
			"}";
	}

	std::string Shader::getDefaultFragmentShaderCode()
	{
		return
			"#version 100								\n"
			"precision mediump float;                   \n"
			"varying vec4 v_vColor;		 				\n"
			"void main()                                \n"
			"{                                          \n"
			"  gl_FragColor = v_vColor;					\n"
			"}                                          \n";
	}
}