#include "Sandbox.h"

#ifdef __SANDBOX__

#include "Helper.h"

#include "../../Base/Math/MathHelper.h"
#include "../../Orbis/Core/TimeManager.h"
using namespace Math;
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
	std::vector<STransform> Sandbox::m_transforms;
	const int Sandbox::NUM_BLOCKS = 1000;
	const float Sandbox::MIN_BLOCK_EXTENT = 0.01f;
	const float Sandbox::MAX_BLOCK_EXTENT = 0.05f;

	void Sandbox::Run()
	{
		TimeManager::GetInstance()->Reset();
		Helper::InitSDL();
		InitGL();

		bool quit = false;
		SDL_Event e;

		Helper::SetStartTicks(TimeManager::GetInstance()->GetTicks());
		Helper::SetNumFrames(0);

		while (!quit)
		{
			TimeManager::GetInstance()->Update();
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
		UpdateTransforms();
		UpdateVertexArray();
		glEnableVertexAttribArray(m_positionHandle);
		glEnableVertexAttribArray(m_texCoordHandle);
		glVertexAttribPointer(m_positionHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(m_vertices[0]));
		glVertexAttribPointer(m_texCoordHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(m_vertices[2]));

		// draw 
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, &m_indices[0]);

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
		InitIndexArray();
		InitTransforms();
	}

	void Sandbox::InitIndexArray()
	{
		const int NUM_VERTICES = 4;
		std::vector<GLshort> indices = { 0, 1, 2, 2, 1, 3 };

		m_indices.clear();
		m_indices.reserve(NUM_BLOCKS * indices.size());
		for (int i = 0; i < NUM_BLOCKS; i++)
		{
			m_indices.insert(m_indices.end(), indices.begin(), indices.end());

			// compute offset for inserted indices
			for (unsigned int j = 0; j < indices.size(); j++)
				m_indices[i * indices.size() + j] += NUM_VERTICES * i;
		}
	}

	void Sandbox::UpdateVertexArray()
	{
		const int VERTEX_SIZE = 4;
		std::vector<GLfloat> vertices = { 
			-1, -1, 0.0f, 0.0f,	// left bottom
			 1, -1, 1.0f, 0.0f,	// right bottom
			-1,  1, 0.0f, 1.0f,	// left top
			 1,  1, 1.0f, 1.0f	// right top
		};

		m_vertices.clear();
		m_vertices.reserve(NUM_BLOCKS * vertices.size());
		for (int i = 0; i < NUM_BLOCKS; i++)
		{
			m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());

			// apply scale
			for (unsigned int j = 0; j < vertices.size() / VERTEX_SIZE; j++)
			{
				m_vertices[i * vertices.size() + j * VERTEX_SIZE] *= m_transforms[i].extent;
				m_vertices[i * vertices.size() + j * VERTEX_SIZE] += m_transforms[i].positionX;
				m_vertices[i * vertices.size() + j * VERTEX_SIZE + 1] *= m_transforms[i].extent;
				m_vertices[i * vertices.size() + j * VERTEX_SIZE + 1] += m_transforms[i].positionY;
			}
		}
	}

	void Sandbox::InitTransforms()
	{
		for (unsigned int i = 0; i < NUM_BLOCKS; i++)
		{
			STransform transform;
			transform.extent = MIN_BLOCK_EXTENT + (MAX_BLOCK_EXTENT - MIN_BLOCK_EXTENT) * MathHelper::GetRandom();
			transform.isGrowing = rand() % 2 == 0 ? true : false;
			transform.positionX = MathHelper::GetRandom() * 2.0f - 1.0f;
			transform.positionY = MathHelper::GetRandom() * 2.0f - 1.0f;
			m_transforms.push_back(transform);
		}
	}

	void Sandbox::UpdateTransforms()
	{
		float dt = TimeManager::GetInstance()->GetDeltaSeconds();
		for (unsigned int i = 0; i < m_transforms.size(); i++)
		{
			m_transforms[i].extent += m_transforms[i].isGrowing ? dt * 0.01f : dt * -0.01f;

			if (m_transforms[i].extent < MIN_BLOCK_EXTENT)
				m_transforms[i].isGrowing = true;

			if (m_transforms[i].extent > MAX_BLOCK_EXTENT)
				m_transforms[i].isGrowing = false;
		}
	}
}

#endif // __SANDBOX__