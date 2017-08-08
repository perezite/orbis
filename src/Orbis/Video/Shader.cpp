#include "Shader.h"

#include "../../Base/System/Exception.h"
using namespace System;

namespace Video
{
	const std::string Shader::m_vertexShaderCode = 
			"attribute vec4 a_vPosition;	\n \
			attribute vec4 a_vColor;		\n \
			varying vec4 v_vColor;			\n \
			void main()						\n \
			{								\n \
				gl_Position = a_vPosition;	\n \
				v_vColor = a_vColor;		\n \
			}								\n ";

	Shader::Shader()
	{
		// load the shaders
		m_vertexShader = LoadShader(m_vertexShaderCode, GL_VERTEX_SHADER);
		m_fragmentShader = LoadShader(m_fragmentShaderCode, GL_FRAGMENT_SHADER);

		// initialize the shader program
		m_shaderProgram = glCreateProgram();
		if (m_shaderProgram == 0)
			throw Exception("Error creating shader program");
		glAttachShader(m_shaderProgram, m_vertexShader);
		glAttachShader(m_shaderProgram, m_fragmentShader);
	}

	Shader::~Shader()
	{
		
	}

	void Shader::SetFragmentShaderCode(std::string code)
	{
		m_fragmentShaderCode = code;
	}

	GLuint Shader::LoadShader(std::string shaderCode, GLenum type)
	{
		GLuint shader;
		GLint compiled;

		shader = glCreateShader(type);
		if (shader != 0)
		{
			const char* shaderCodeData = shaderCode.c_str();
			glShaderSource(shader, 1, &shaderCodeData, NULL);
			glCompileShader(shader);

			glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
			if (!compiled)
			{
				GLint infoLen = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

				std::string infoLogString;
				if (infoLen > 1)
				{
					char* infoLog = new char[infoLen];
					glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
					infoLogString = std::string(infoLog);
					delete[] infoLog;
				}
				glDeleteShader(shader);

				throw Exception("Error compiling shader: " + infoLogString);
			}
		}

		return shader;
	}
}