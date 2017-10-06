#include "Renderer.h"

#include "../../Base/System/Exception.h"
using namespace System;

namespace
{
	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;
}

namespace Video
{
	Renderer::Renderer()
	{
		gProgramID = glCreateProgram();
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* vertexShaderSource[] =
		{
			"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
		};
		glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
		glAttachShader(gProgramID, vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* fragmentShaderSource[] =
		{
			"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 0.0, 0.0, 1.0 ); }"
		};
		glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glAttachShader(gProgramID, fragmentShader);

		glLinkProgram(gProgramID);
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
		glUseProgram(NULL);
	}


	/*
	Renderer::~Renderer()
	{
	}

	void Renderer::BeginPrimitive(RenderMode renderMode)
	{
		m_renderMode = renderMode;
		m_vertices.clear();
		m_colors.clear();
		m_indices.clear();
	}

	void Renderer::EndPrimitive(float rotation)
	{
		m_shader.SetIndices(m_indices);
		m_shader.SetVertices(m_vertices, m_colors);
		m_shader.Render(m_vertices, m_colors, rotation, m_renderMode);
	}

	void Renderer::SetVertex2D(Vector2D position)
	{
		m_vertices.push_back(position);
		m_colors.push_back(Color(0.0f, 0.0f, 1.0f, 1.0f));

		unsigned int lastIndex = m_indices.empty() ? -1 : m_indices.back();
		m_indices.push_back(lastIndex + 1);

	}
	*/
}