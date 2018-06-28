#include "Shader.h"

#include "VideoManager.h"

#include "../Core/AssetHelper.h"
#include "../Libraries/GL.h"
#include "../Components/Camera.h"
using namespace core;
using namespace components;

#include "../../Base/System/Exception.h"
using namespace base::system;

namespace
{
	// compile the shader code
	GLuint compile(std::string shaderCode, GLenum type, GLuint programId)
	{
		GLuint shader;
		GLint compiled;

		shader = glCreateShader(type);
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

		return shader;
	}

	// link the shader program
	void link(GLuint programId)
	{
		glLinkProgram(programId);

		GLint linked;
		glGetProgramiv(programId, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLint infoLen = 0;
			std::string infoLogString;

			glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char* infoLog = new char[infoLen];
				glGetProgramInfoLog(programId, infoLen, NULL, infoLog);
				infoLogString = std::string(infoLog);
				delete[] infoLog;
			}

			glDeleteProgram(programId);
			throw Exception("Error linking shader program: " + infoLogString);
		}
	}
}

namespace video
{
	Shader::Shader(std::string vertexShaderAssetPath, std::string fragmentShaderAssetPath)
	{
		VideoManager::getInstance();

		m_programId = glCreateProgram();

		std::string vertexShaderCode = AssetHelper::loadTextAsset(vertexShaderAssetPath);
		GLuint vertexShader = compile(vertexShaderCode, GL_VERTEX_SHADER, m_programId);
		glAttachShader(m_programId, vertexShader);

		std::string fragmentShaderCode = AssetHelper::loadTextAsset(fragmentShaderAssetPath);
		GLuint fragmentShader = compile(fragmentShaderCode, GL_FRAGMENT_SHADER, m_programId);
		glAttachShader(m_programId, fragmentShader);

		link(m_programId);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_programId);
	}

	int Shader::getAttributeLocation(std::string id)
	{
		GLint location = glGetAttribLocation(m_programId, id.c_str());
		return location;
	}

	void Shader::setUniform(std::string id, int value)
	{
		GLint handle = glGetUniformLocation(m_programId, id.c_str());
		glUniform1i(handle, value);
	}

	void Shader::setUniform(std::string id, const Color & color)
	{
		GLint handle = glGetUniformLocation(m_programId, id.c_str());

		glUniform4f(handle, color.r, color.g, color.b, color.a);
	}

	void Shader::use()
	{
		glUseProgram(m_programId);
	}

	void Shader::unuse()
	{
		glUseProgram(0);
	}
}