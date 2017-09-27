#include "Shader.h"

#include "../../Base/System/Exception.h"
using namespace System;

namespace Video
{
	const std::string Shader::VertexShaderCode =
		"attribute vec4 a_vPosition;		\n \
		attribute vec4 a_vColor;			\n \
		attribute float a_fRotation;		\n \
		varying vec4 v_vColor;				\n \
		mat4 rotationMat =											\n \
			mat4(cos(a_fRotation), sin(a_fRotation), 0, 0,					\n \
			-sin(a_fRotation), cos(a_fRotation), 0, 0,						\n \
			0, 0, 1, 0,														\n \
			0, 0, 0, 1);													\n \
		void main()							\n \
		{									\n \
			gl_Position = rotationMat * a_vPosition;	\n \
			v_vColor = a_vColor;			\n \
		}									\n ";

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

		// link and use the shader program
		Link();
		glUseProgram(m_shaderProgram);

		// get attribute locatons
		m_positionAttributeLocation = glGetAttribLocation(m_shaderProgram, "a_vPosition");
		m_colorAttributeLocation = glGetAttribLocation(m_shaderProgram, "a_vColor");
		m_rotationAttributeLocation = glGetAttribLocation(m_shaderProgram, "a_fRotation");
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_shaderProgram);
	}

	void Shader::Render(std::vector<Vector2D> positions, std::vector<Color> colors, float rotation, RenderMode renderMode)
	{
		// number of elements per color
		static const int32_t ColorNumElements = 4;
		static const int32_t PositionNumElements = 3;
		static const int32_t VertexSize = sizeof(GLfloat) * (PositionNumElements + ColorNumElements);

		// setup
		m_vertexArray = GetVertexArray(positions, colors);
		glEnableVertexAttribArray(m_positionAttributeLocation);
		glEnableVertexAttribArray(m_colorAttributeLocation);
		glVertexAttribPointer(m_positionAttributeLocation, PositionNumElements, GL_FLOAT, GL_FALSE, VertexSize, m_vertexArray);
		glVertexAttribPointer(m_colorAttributeLocation, ColorNumElements, GL_FLOAT, GL_FALSE, VertexSize, &m_vertexArray[PositionNumElements]);
		glVertexAttrib1f(m_rotationAttributeLocation, rotation);

		// render
		glDrawArrays(renderMode, 0, positions.size());

		// cleanup
		delete[] m_vertexArray;
		glDisableVertexAttribArray(m_positionAttributeLocation);
		glDisableVertexAttribArray(m_colorAttributeLocation);
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
		GLfloat *vertexArray = new GLfloat[numberOfElements];
		for (unsigned int i = 0; i < positions.size(); i++)
		{
			vertexArray[i * 7 + 0] = positions[i].GetX();
			vertexArray[i * 7 + 1] = positions[i].GetY();
			vertexArray[i * 7 + 2] = 0.0f;
			vertexArray[i * 7 + 3] = colors[i].GetRed();
			vertexArray[i * 7 + 4] = colors[i].GetGreen();
			vertexArray[i * 7 + 5] = colors[i].GetBlue();
			vertexArray[i * 7 + 6] = colors[i].GetAlpha();
		}

		return vertexArray;
	}
}