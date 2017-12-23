#include "Sandbox.h"

#ifdef __SANDBOX__

#include "Helper.h"

#include "../../Orbis/Core/TimeManager.h"
using namespace Core;

#include <stdio.h>
#include <string>
#include <iostream>

namespace Sandboxing
{
	GLint Sandbox::m_positionHandle = -1;
	GLint Sandbox::m_texCoordHandle = -1;
	GLint Sandbox::m_samplerHandle = -1;
	GLuint Sandbox::m_vbo = 0;
	GLuint Sandbox::m_ibo = 0;
	GLuint Sandbox::m_texture = 0;

	void Sandbox::Run()
	{
		Helper::InitSDL();
		InitGL();

		bool quit = false;
		SDL_Event e;

		Helper::SetStartTicks(TimeManager::GetInstance()->GetTicks());
		Helper::SetNumFrames(0);

		while (!quit)
		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN || e.type == SDL_FINGERDOWN)
				{
					quit = true;
				}
			}

			Render();

			SDL_GL_SwapWindow(Helper::GetWindow());

			Helper::LogPerformance();
		}

		Helper::Close();
	}

	void Sandbox::Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// set shader
		glUseProgram(Helper::GetShaderProgramHandle());

		// set texture
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(m_samplerHandle, 0);

		// set buffers
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glEnableVertexAttribArray(m_positionHandle);
		glEnableVertexAttribArray(m_texCoordHandle);
		glVertexAttribPointer(m_positionHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
		glVertexAttribPointer(m_texCoordHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)(0 + 2 * sizeof(GL_FLOAT)));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

		// draw 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		// cleanup
		glDisableVertexAttribArray(m_texCoordHandle);
		glDisableVertexAttribArray(m_positionHandle);
		glDisable(GL_TEXTURE_2D);
		glUseProgram(0);
	}

	void Sandbox::InitGL()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		// init shaders
		GLuint programHandle = Helper::CreateShaderProgram();
		GLuint vertexShader = Helper::LoadShader(Helper::GetVertexShaderCode(), GL_VERTEX_SHADER);
		GLuint fragmentShader = Helper::LoadShader(Helper::GetFragmentShaderCode(), GL_FRAGMENT_SHADER);
		glAttachShader(programHandle, vertexShader);
		glAttachShader(programHandle, fragmentShader);
		glLinkProgram(programHandle);
		glUseProgram(programHandle);

		// get shader handles
		m_positionHandle = glGetAttribLocation(programHandle, "a_vPosition");
		m_texCoordHandle = glGetAttribLocation(programHandle, "a_texCoord");
		m_samplerHandle = glGetUniformLocation(programHandle, "s_texture");
		
		// init vertex buffer
		GLfloat vertexData[] =
		{
			-0.5f, -0.5f,	// left bottom pos
			0.0f,  0.0f,	// left bottom tex
			0.5f, -0.5f,	// right bottom pos
			1.0f,  0.0f,	// right bottom tex
			-0.5f,  0.5f,	// left top pos pos
			0.0f,  1.0f,	// left top tex
			0.5f,  0.5f,	// right top pos
			1.0f,  1.0f		// right top tex
		};
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, 2 * 8 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

		// init index buffer
		GLuint indexData[] = { 0, 1, 2, 2, 1, 3 };
		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

		// init texture
		m_texture = Helper::LoadTexture(Helper::GetAssetFilePath("Textures/YellowBlock.png"), true);
	}
}

#endif // __SANDBOX__