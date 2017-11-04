#include "Shader.h"

#include "VideoManager.h"

#include "../Core/AssetHelper.h"
#include "../Libraries/GL.h"
using namespace Core;
using namespace Libraries;

#include "../../Base/System/Exception.h"
using namespace System;

namespace
{
	// the shader program id
	GLuint programId = -1;

	// the vertex position attribute handle
	GLint positionAttributeHandle = -1;

	// the tex coord attribute handle
	GLint texCoordAttributeHandle = -1;

	// the transform uniform handle
	GLint transformUniformHandle = -1;

	// the sample uniform handle
	GLint samplerUniformHandle = -1;

	// compile the shader code
	GLuint Compile(std::string shaderCode, GLenum type)
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
	void Link()
	{
		glLinkProgram(programId);

		GLint linked;
		GL::GetProgramParameter(programId, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLint infoLen = 0;
			std::string infoLogString;

			GL::GetProgramParameter(programId, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char* infoLog = new char[infoLen];
				GL::GetProgramInfoLog(programId, infoLen, NULL, infoLog);
				infoLogString = std::string(infoLog);
				delete[] infoLog;
			}

			GL::DeleteProgram(programId);
			throw Exception("Error linking shader program: " + infoLogString);
		}
	}
}

namespace Video
{
	Shader::Shader(std::string vertexAssetPath, std::string fragmentAssetPath)
	{
		VideoManager::GetInstance();

		programId = GL::CreateProgram();

		std::string vertexShaderCode = AssetHelper::LoadTextAsset(vertexAssetPath);
		GLuint vertexShader = Compile(vertexShaderCode, GL_VERTEX_SHADER);
		GL::AttachShader(programId, vertexShader);

		std::string fragmentShaderCode = AssetHelper::LoadTextAsset(fragmentAssetPath);
		GLuint fragmentShader = Compile(fragmentShaderCode, GL_FRAGMENT_SHADER);
		GL::AttachShader(programId, fragmentShader);

		Link();

		positionAttributeHandle = GL::GetAttributeLocation(programId, "a_vPosition");
		texCoordAttributeHandle = GL::GetAttributeLocation(programId, "a_vTexCoord");
		transformUniformHandle = GL::GetUniformLocation(programId, "u_mTransform");
		samplerUniformHandle = GL::GetUniformLocation(programId, "u_sSampler");
	}

	Shader::~Shader()
	{
		GL::DeleteProgram(programId);
	}

	int Shader::GetPositionAttributeHandle()
	{
		return positionAttributeHandle;
	}

	int Shader::GetTexCoordAttributeHandle()
	{
		return texCoordAttributeHandle;
	}

	void Shader::SetTransformUniform(const Matrix4& mat)
	{
		Matrix4 transposed = mat.Transposed();
		GL::UniformMatrix4(transformUniformHandle, 1, GL_FALSE, transposed.GetValues());
	}

	void Shader::SetSamplerUniform(int sampler)
	{
		GL::Uniform(samplerUniformHandle, sampler);
	}

	void Shader::Use()
	{
		GL::UseProgram(programId);
	}

	void Shader::Unuse()
	{
		GL::UseProgram(0);
	}
}