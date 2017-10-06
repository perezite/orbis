#include "Shader.h"

#include "../Helpers/VertexHelper.h"
using namespace Helpers;

#include "../../Base/System/Exception.h"
using namespace System;

namespace
{
	/*
	mat4 rotationMat =											\n \
	mat4(cos(a_fRotation), sin(a_fRotation), 0, 0,					\n \
	-sin(a_fRotation), cos(a_fRotation), 0, 0,						\n \
	0, 0, 1, 0,														\n \
	0, 0, 0, 1);													\n \
	*/

	// the vertex shader code
	const std::string VertexShaderCode =
		"attribute vec2 a_vPosition;		\n \
		attribute float a_fRotation;		\n \
		void main()							\n \
		{									\n \
			gl_Position = vec4( a_vPosition.xy, 0, 1 );		\n \
		}									\n ";

	// the fragment shader code
	const std::string FragmentShaderCode =
		"void main() { gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 ); }";

	// the shader program id
	GLuint gProgramID = 0;

	// the vertex position location
	GLint gVertexPositionLocation = -1;

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
		glLinkProgram(gProgramID);

		GLint linked;
		glGetProgramiv(gProgramID, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLint infoLen = 0;
			std::string infoLogString;

			glGetProgramiv(gProgramID, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char* infoLog = new char[infoLen];
				glGetProgramInfoLog(gProgramID, infoLen, NULL, infoLog);
				infoLogString = std::string(infoLog);
				delete[] infoLog;
			}

			glDeleteProgram(gProgramID);
			throw Exception("Error linking shader program: " + infoLogString);
		}
	}
}

namespace Video
{
	Shader::Shader()
	{
		gProgramID = glCreateProgram();

		GLuint vertexShader = Compile(VertexShaderCode, GL_VERTEX_SHADER);
		glAttachShader(gProgramID, vertexShader);

		GLuint fragmentShader = Compile(FragmentShaderCode, GL_FRAGMENT_SHADER);
		glAttachShader(gProgramID, fragmentShader);

		Link();

		gVertexPositionLocation = glGetAttribLocation(gProgramID, "a_vPosition");
	}

	Shader::~Shader()
	{
		glDeleteProgram(gProgramID);
	}

	int Shader::GetPositionLocation()
	{
		return gVertexPositionLocation;
	}

	void Shader::Use()
	{
		glUseProgram(gProgramID);
	}

	void Shader::Unuse()
	{
		glUseProgram(0);
	}
}