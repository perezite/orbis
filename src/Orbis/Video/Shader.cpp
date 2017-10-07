#include "Shader.h"

#include "../Core/AssetHelper.h"
using namespace Core;

#include "../../Base/System/Exception.h"
using namespace System;

namespace
{
	// the shader program id
	GLuint programId = 0;

	// the vertex position location
	GLint positionAttributeLocation = -1;

	// the rotation attribute location
	GLint rotationUniformLocation = -1;

	// compile the shader code
	GLuint Compile(std::string shaderCode, GLenum type)
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

	// link the shader program
	void Link()
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

namespace Video
{
	Shader::Shader(std::string vertexAssetPath, std::string fragmentAssetPath)
	{
		programId = glCreateProgram();

		std::string vertexShaderCode = AssetHelper::LoadTextAsset(vertexAssetPath);
		GLuint vertexShader = Compile(vertexShaderCode, GL_VERTEX_SHADER);
		glAttachShader(programId, vertexShader);

		std::string fragmentShaderCode = AssetHelper::LoadTextAsset(fragmentAssetPath);
		GLuint fragmentShader = Compile(fragmentShaderCode, GL_FRAGMENT_SHADER);
		glAttachShader(programId, fragmentShader);

		Link();

		positionAttributeLocation = glGetAttribLocation(programId, "a_vPosition");
		rotationUniformLocation = glGetUniformLocation(programId, "u_fRotation");
	}

	Shader::~Shader()
	{
		glDeleteProgram(programId);
	}

	int Shader::GetPositionAttributeLocation()
	{
		return positionAttributeLocation;
	}

	void Shader::SetRotationUniform(float rotation)
	{
		glUniform1f(rotationUniformLocation, rotation);
	}

	void Shader::Use()
	{
		glUseProgram(programId);
	}

	void Shader::Unuse()
	{
		glUseProgram(0);
	}
}