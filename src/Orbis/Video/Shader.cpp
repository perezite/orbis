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

	Shader::Shader()
	{
		// load the shaders
		m_vertexShader = Compile(VertexShaderCode, GL_VERTEX_SHADER);
		m_fragmentShader = Compile(FragmentShaderCode, GL_FRAGMENT_SHADER);

		// initialize the shader program
		m_shaderProgram = glCreateProgram();
		glAttachShader(m_shaderProgram, m_vertexShader);
		glAttachShader(m_shaderProgram, m_fragmentShader);

		// bind shader attributes to constants
		glBindAttribLocation(m_shaderProgram, PositionShaderAttributeLocation, "a_vPosition");
		glBindAttribLocation(m_shaderProgram, ColorShaderAttributeLocation, "a_vColor");

		// link and use the shader program
		Link();
		glUseProgram(m_shaderProgram);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_shaderProgram);
	}

	void Shader::Render(std::vector<Vector2D> positions, std::vector<Color> colors, RenderMode renderMode)
	{
		// number of elements per color
		static const int32_t ColorNumElements = 4;
		static const int32_t PositionNumElements = 3;
		static const int32_t VertexSize = sizeof(GLfloat) * (PositionNumElements + ColorNumElements);

		// setup
		m_vertexArray = GetVertexArray(positions, colors);
		glEnableVertexAttribArray(PositionShaderAttributeLocation);
		glEnableVertexAttribArray(ColorShaderAttributeLocation);
		glVertexAttribPointer(PositionShaderAttributeLocation, PositionNumElements, GL_FLOAT, GL_FALSE, VertexSize, m_vertexArray);
		glVertexAttribPointer(ColorShaderAttributeLocation, ColorNumElements, GL_FLOAT, GL_FALSE, VertexSize, &m_vertexArray[PositionNumElements]);

		// render
		glDrawArrays(renderMode, 0, positions.size());

		// cleanup
		delete[] m_vertexArray;
		glDisableVertexAttribArray(PositionShaderAttributeLocation);
		glDisableVertexAttribArray(ColorShaderAttributeLocation);
	}

	GLuint Shader::Compile(std::string shaderCode, GLenum type)
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

	void Shader::Link()
	{
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

	GLfloat* Shader::GetVertexArray(std::vector<Vector2D> positions, std::vector<Color> colors)
	{
		int numberOfElements = positions.size() * (3 + 4);
		GLfloat *vertexBuffer = new GLfloat[numberOfElements];
		for (unsigned int i = 0; i < positions.size(); i++)
		{
			vertexBuffer[i * 7 + 0] = positions[i].GetX();
			vertexBuffer[i * 7 + 1] = positions[i].GetY();
			vertexBuffer[i * 7 + 2] = 0.0f;
			vertexBuffer[i * 7 + 3] = colors[i].GetRed();
			vertexBuffer[i * 7 + 4] = colors[i].GetGreen();
			vertexBuffer[i * 7 + 5] = colors[i].GetBlue();
			vertexBuffer[i * 7 + 6] = colors[i].GetAlpha();
		}

		return vertexBuffer;
	}
}