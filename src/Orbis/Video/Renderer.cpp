#include "Renderer.h"

#include "VideoManager.h"

#include "../../Base/System/Exception.h"
using namespace System;

namespace
{
	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;

	const std::string VertexShaderCode =
		"attribute vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.xy, 0, 1 ); }";

	const std::string FragmentShaderCode =
		"void main() { gl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 ); }";

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
	Renderer::Renderer()
	{
		gProgramID = glCreateProgram();

		GLuint vertexShader = Compile(VertexShaderCode, GL_VERTEX_SHADER);
		glAttachShader(gProgramID, vertexShader);

		GLuint fragmentShader = Compile(FragmentShaderCode, GL_FRAGMENT_SHADER);
		glAttachShader(gProgramID, fragmentShader);

		Link();

		gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");

		glClearColor(0.f, 0.f, 0.f, 1.f);

		GLfloat vertexData[] =
		{
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.0f,  0.5f
		};

		GLuint indexData[] = { 0, 1, 2 };

		glGenBuffers(1, &gVBO);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glBufferData(GL_ARRAY_BUFFER, 2 * 3 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

		glGenBuffers(1, &gIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
	}

	Renderer::~Renderer()
	{
		glDeleteProgram(gProgramID);
	}

	void Renderer::BeginPrimitive(RenderMode renderMode)
	{
	}

	void Renderer::EndPrimitive(float rotation)
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(gProgramID);
		glEnableVertexAttribArray(gVertexPos2DLocation);

		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);

		glDisableVertexAttribArray(gVertexPos2DLocation);
		glUseProgram(0);
	}
}