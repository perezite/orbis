#include "Shader_v2.h"

#include "VideoManager.h"

#include "../Core/AssetHelper.h"
#include "../Libraries/GL.h"
#include "../Components/Camera.h"
using namespace Core;
using namespace Components;

#include "../../Base/System/Exception.h"
using namespace System;

namespace
{
	// compile the shader code
	GLuint Compile(std::string shaderCode, GLenum type, GLuint programId)
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
	void Link(GLuint programId)
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
	Shader_v2* Shader_v2::GetDiffuseShader()
	{
		static Shader_v2 diffuseShader("Shaders/Diffuse.vs", "Shaders/Diffuse.frag");
		return &diffuseShader;
	}

	Shader_v2* Shader_v2::GetFlatShader()
	{
		static Shader_v2 flatShader("Shaders/Flat.vs", "Shaders/Flat.frag");
		return &flatShader;
	}

	Shader_v2::Shader_v2(std::string vertexAssetPath, std::string fragmentAssetPath)
	{
		m_programId = glCreateProgram();

		std::string vertexShaderCode = AssetHelper::LoadTextAsset(vertexAssetPath);
		GLuint vertexShader = Compile(vertexShaderCode, GL_VERTEX_SHADER, m_programId);
		glAttachShader(m_programId, vertexShader);

		std::string fragmentShaderCode = AssetHelper::LoadTextAsset(fragmentAssetPath);
		GLuint fragmentShader = Compile(fragmentShaderCode, GL_FRAGMENT_SHADER, m_programId);
		glAttachShader(m_programId, fragmentShader);

		Link(m_programId);
	}

	Shader_v2::~Shader_v2()
	{
		glDeleteProgram(m_programId);
	}

	int Shader_v2::GetAttributePosition(std::string id)
	{
		GLint location = glGetAttribLocation(m_programId, id.c_str());
		return location;
	}

	void Shader_v2::SetUniform(std::string id, int value)
	{
		GLint handle = glGetUniformLocation(m_programId, id.c_str());
		glUniform1i(handle, value);
	}

	void Shader_v2::SetUniform(std::string id, const Color & color)
	{
		GLint handle = glGetUniformLocation(m_programId, id.c_str());

		glUniform4f(handle, color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
	}

	void Shader_v2::SetUniform(std::string id, const Matrix4 & mat)
	{
		GLint handle = glGetUniformLocation(m_programId, id.c_str());
		glUniformMatrix4fv(handle, 1, GL_FALSE, mat.GetValues());
	}

	void Shader_v2::Use()
	{
		glUseProgram(m_programId);
	}

	void Shader_v2::Unuse()
	{
		glUseProgram(0);
	}

	const bool Shader_v2::operator==(const Shader_v2 &other) const
	{
		return m_programId > 0 && m_programId == other.m_programId;
	}
}