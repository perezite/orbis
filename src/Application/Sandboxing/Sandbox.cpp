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
	GLuint Sandbox::m_texture = 0;
	std::vector<GLfloat> Sandbox::m_vertices;
	std::vector<GLushort> Sandbox::m_indices;

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
		// set states
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// set shader
		glUseProgram(Helper::GetShaderProgramHandle());

		// set texture
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(m_samplerHandle, 0);

		// set arrays
		UpdateVertexArray();
		glEnableVertexAttribArray(m_positionHandle);
		glEnableVertexAttribArray(m_texCoordHandle);
		glVertexAttribPointer(m_positionHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(m_vertices[0]));
		glVertexAttribPointer(m_texCoordHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(m_vertices[2]));

		// draw 
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, &m_indices[0]);

		// cleanup
		glDisableVertexAttribArray(m_texCoordHandle);
		glDisableVertexAttribArray(m_positionHandle);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
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
		
		// init texture
		m_texture = Helper::LoadTexture(Helper::GetAssetFilePath("Textures/YellowBlock.png"), true);

		// init arrays
		m_indices = { 0, 1, 2, 2, 1, 3 };
	}

	void Sandbox::UpdateVertexArray()
	{
		m_vertices = { 
			-0.5f, -0.5f, 0.0f, 0.0f,	// left bottom
			 0.5f, -0.5f, 1.0f, 0.0f,	// right bottom
			-0.5f,  0.5f, 0.0f, 1.0f,	// left top
			 0.5f,  0.5f, 1.0f, 1.0f	// right top
		};
	}
}

#endif // __SANDBOX__