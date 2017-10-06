#include "Shader.h"

#include "../Helpers/VertexHelper.h"
using namespace Helpers;

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

	// the vertex shader code
	const std::string VertexShaderCode =
		"attribute vec2 a_vPosition;										\n \
		uniform float u_fRotation;											\n \
																			\n \
		mat4 rotationMat =													\n \
			mat4(cos(u_fRotation), sin(u_fRotation), 0, 0,					\n \
			- sin(u_fRotation), cos(u_fRotation), 0, 0,						\n \
			0, 0, 1, 0,														\n \
			0, 0, 0, 1);													\n \
																			\n \
		void main()															\n \
		{																	\n \
			gl_Position = rotationMat * vec4( a_vPosition.xy, 0, 1 );		\n \
		}																	\n ";

	// the fragment shader code
	const std::string FragmentShaderCode =
		"void main() { gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 ); }";

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
	Shader::Shader()
	{
		programId = glCreateProgram();

		GLuint vertexShader = Compile(VertexShaderCode, GL_VERTEX_SHADER);
		glAttachShader(programId, vertexShader);

		GLuint fragmentShader = Compile(FragmentShaderCode, GL_FRAGMENT_SHADER);
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