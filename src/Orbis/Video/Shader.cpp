#include "Shader.h"

#include "../../Base/System/Exception.h"
using namespace System;

namespace Video
{
	const std::string Shader::VertexShaderCode = 
		"attribute vec4 a_vPosition;	\n \
		attribute vec4 a_vColor;		\n \
		varying vec4 v_vColor;			\n \
		void main()						\n \
		{								\n \
			gl_Position = a_vPosition;	\n \
			v_vColor = a_vColor;		\n \
		}								\n ";

	const std::string Shader::FragmentShaderCode =
		#ifdef WIN32
			"#version 130 				\n"
		#endif
		"precision mediump float;       \n"
		"varying vec4 v_vColor;		 	\n"
		"void main()                    \n"
		"{                              \n"
		"   gl_FragColor = v_vColor;	\n"
		"}                              \n";

	Shader::~Shader()
	{
		glDeleteProgram(m_shaderProgram);
	}

	Shader::Shader()
	{
		// load the shaders
		m_vertexShader = LoadShader(VertexShaderCode, GL_VERTEX_SHADER);
		m_fragmentShader = LoadShader(FragmentShaderCode, GL_FRAGMENT_SHADER);

		// initialize the shader program
		m_shaderProgram = glCreateProgram();
		if (m_shaderProgram == 0)
			throw Exception("Error creating shader program");
		glAttachShader(m_shaderProgram, m_vertexShader);
		glAttachShader(m_shaderProgram, m_fragmentShader);

		// Bind a_vPosition to attribute 0 and a_vColor to 1
		glBindAttribLocation(m_shaderProgram, PositionShaderAttributeLocation, "a_vPosition");
		glBindAttribLocation(m_shaderProgram, ColorShaderAttributeLocation, "a_vColor");

		// Link the program
		glLinkProgram(m_shaderProgram);

		// Check the link status
		GLint linked;
		glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLint infoLen = 0;
			std::string infoLogString;

			glGetProgramiv(m_shaderProgram, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char* infoLog = new char[infoLen];
				glGetProgramInfoLog(m_shaderProgram, infoLen, NULL, infoLog);
				infoLogString = std::string(infoLog);
				delete[] infoLog;
			}

			glDeleteProgram(m_shaderProgram);
			throw Exception("Error linking shader program: " + infoLogString);
		}
	}

	void Shader::Draw(RenderMode renderMode)
	{
		static const int32_t PositionNumElements = 3;
		static const int32_t ColorNumElements = 4;
		static const int32_t VertexSize = sizeof(GLfloat) * (PositionNumElements + ColorNumElements);
		static const float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };

		// setup the shader for drawing
		glUseProgram(m_shaderProgram);
		glEnableVertexAttribArray(PositionShaderAttributeLocation);
		glEnableVertexAttribArray(ColorShaderAttributeLocation);

		// copy the vertices into an array
		int numberOfElements = m_vertexPositions.size() * (3 + 4);
		GLfloat *vertexData = new GLfloat[numberOfElements];
		for (unsigned int i = 0; i < m_vertexPositions.size(); i++)
		{
			vertexData[i * 7 + 0] = m_vertexPositions[i].GetX();
			vertexData[i * 7 + 1] = m_vertexPositions[i].GetY();
			vertexData[i * 7 + 2] = 0.0f;
			vertexData[i * 7 + 3] = color[0];
			vertexData[i * 7 + 4] = color[1];
			vertexData[i * 7 + 5] = color[2];
			vertexData[i * 7 + 6] = color[3];
		}

		// draw
		glVertexAttribPointer(PositionShaderAttributeLocation, PositionNumElements, GL_FLOAT, GL_FALSE, VertexSize,vertexData);
		glVertexAttribPointer(ColorShaderAttributeLocation, ColorNumElements, GL_FLOAT, GL_FALSE, VertexSize, &vertexData[PositionNumElements]);
		glDrawArrays(renderMode, 0, m_vertexPositions.size());

		// cleanup
		glDisableVertexAttribArray(PositionShaderAttributeLocation);
		glDisableVertexAttribArray(ColorShaderAttributeLocation);
		delete[] vertexData;
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