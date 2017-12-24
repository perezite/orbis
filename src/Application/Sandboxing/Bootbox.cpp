#include "Bootbox.h"

#ifdef __SANDBOX__

#include "Helper.h"

#include "../../Base/Math/MathHelper.h"
#include "../../Orbis/Core/TimeManager.h"
using namespace Math;
using namespace Core;

#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>
#include <algorithm>

namespace Sandboxing
{
	GLint Bootbox::m_positionHandle = -1;
	GLint Bootbox::m_texCoordHandle = -1;
	GLint Bootbox::m_samplerHandle = -1;
	std::vector<GLuint> Bootbox::m_textures;
	std::vector<GLfloat> Bootbox::m_vertices;
	std::vector<GLushort> Bootbox::m_indices;
	std::vector<BEntity> Bootbox::m_entities;
	const int Bootbox::NUM_SPRITES = 1000;
	const int Bootbox::VERTICES_PER_SPRITE = 4;
	const int Bootbox::INDICES_PER_SPRITE = 6;
	const float Bootbox::MIN_BLOCK_EXTENT = 0.01f;
	const float Bootbox::MAX_BLOCK_EXTENT = 0.05f;

	void Bootbox::Run()
	{
		srand(42);

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
				if (e.type == SDL_QUIT)
					quit = true;
			}

			Render();

			SDL_GL_SwapWindow(Helper::GetWindow());

			Helper::LogPerformance();
		}

		Helper::Close();
	}

	void Bootbox::Render()
	{
		// set states
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// set shader
		glUseProgram(Helper::GetShaderProgramHandle());
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(m_samplerHandle, 0);

		// set arrays
		UpdateEntities();
		UpdateVertexArray();
		glEnableVertexAttribArray(m_positionHandle);
		glEnableVertexAttribArray(m_texCoordHandle);
		glVertexAttribPointer(m_positionHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(m_vertices[0]));
		glVertexAttribPointer(m_texCoordHandle, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), &(m_vertices[2]));

		// render batched 
		glClear(GL_COLOR_BUFFER_BIT);
		for (unsigned int batchBegin = 0; batchBegin < m_entities.size(); batchBegin++)
		{
			// compute batch
			unsigned int batchEnd = batchBegin;
			for (unsigned int j = batchBegin; j < m_entities.size(); j++)
			{
				if (m_entities[j].texture != m_entities[batchBegin].texture)
					break;
				batchEnd = j;
			}

			// set texture
			glBindTexture(GL_TEXTURE_2D, m_entities[batchBegin].texture);

			// draw
			glDrawElements(GL_TRIANGLES, (batchEnd - batchBegin + 1) * INDICES_PER_SPRITE, GL_UNSIGNED_SHORT, &m_indices[batchBegin * INDICES_PER_SPRITE]);
			batchBegin = batchEnd;
		}

		// cleanup
		glDisableVertexAttribArray(m_texCoordHandle);
		glDisableVertexAttribArray(m_positionHandle);
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glUseProgram(0);
	}

	void Bootbox::InitGL()
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

		// init data
		InitTextures();
		InitIndexArray();
		InitEntities();
	}

	void Bootbox::InitIndexArray()
	{
		std::vector<GLshort> indices = { 0, 1, 2, 2, 1, 3 };

		m_indices.clear();
		m_indices.reserve(NUM_SPRITES * indices.size());
		for (int i = 0; i < NUM_SPRITES; i++)
		{
			m_indices.insert(m_indices.end(), indices.begin(), indices.end());

			// compute offset for inserted indices
			for (unsigned int j = 0; j < indices.size(); j++)
				m_indices[i * indices.size() + j] += VERTICES_PER_SPRITE * i;
		}
	}

	void Bootbox::InitEntities()
	{
		for (unsigned int i = 0; i < NUM_SPRITES; i++)
		{
			BEntity entity;

			// set data and insert
			entity.texture = m_textures[rand() % m_textures.size()];
			entity.extent = MIN_BLOCK_EXTENT + (MAX_BLOCK_EXTENT - MIN_BLOCK_EXTENT) * MathHelper::GetRandom();
			entity.isGrowing = rand() % 2 == 0 ? true : false;
			entity.positionX = MathHelper::GetRandom() * 2.0f - 1.0f;
			entity.positionY = MathHelper::GetRandom() * 2.0f - 1.0f;

			// insert by texture
			int lastIndex = FindLastEntityByTexture(entity.texture);
			int insertIndex = lastIndex >= 0 ? lastIndex + 1 : m_entities.size();
			m_entities.insert(m_entities.begin() + insertIndex, entity);
		}
	}

	void Bootbox::InitTextures()
	{
		m_textures.push_back(Helper::LoadTexture(Helper::GetAssetFilePath("Textures/BlackBlock.png"), true));
		m_textures.push_back(Helper::LoadTexture(Helper::GetAssetFilePath("Textures/BlueBlock.png"), true));
		m_textures.push_back(Helper::LoadTexture(Helper::GetAssetFilePath("Textures/CyanBlock.png"), true));
		m_textures.push_back(Helper::LoadTexture(Helper::GetAssetFilePath("Textures/GreenBlock.png"), true));
		m_textures.push_back(Helper::LoadTexture(Helper::GetAssetFilePath("Textures/GreyBlock.png"), true));
		m_textures.push_back(Helper::LoadTexture(Helper::GetAssetFilePath("Textures/OrangeBlock.png"), true));
		m_textures.push_back(Helper::LoadTexture(Helper::GetAssetFilePath("Textures/PurpleBlock.png"), true));
		m_textures.push_back(Helper::LoadTexture(Helper::GetAssetFilePath("Textures/RedBlock.png"), true));
		m_textures.push_back(Helper::LoadTexture(Helper::GetAssetFilePath("Textures/VioletBlock.png"), true));
		m_textures.push_back(Helper::LoadTexture(Helper::GetAssetFilePath("Textures/YellowBlock.png"), true));
	}

	void Bootbox::UpdateEntities()
	{
		float dt = TimeManager::GetInstance()->GetDeltaSeconds();
		for (unsigned int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i].extent += m_entities[i].isGrowing ? dt * 0.01f : dt * -0.01f;

			if (m_entities[i].extent < MIN_BLOCK_EXTENT)
				m_entities[i].isGrowing = true;

			if (m_entities[i].extent > MAX_BLOCK_EXTENT)
				m_entities[i].isGrowing = false;
		}
	}

	void Bootbox::UpdateVertexArray()
	{
		std::vector<GLfloat> vertices = {
			-1, -1, 0.0f, 0.0f,	// left bottom
			1, -1, 1.0f, 0.0f,	// right bottom
			-1,  1, 0.0f, 1.0f,	// left top
			1,  1, 1.0f, 1.0f	// right top
		};

		m_vertices.clear();
		m_vertices.reserve(NUM_SPRITES * vertices.size());
		for (int i = 0; i < NUM_SPRITES; i++)
		{
			m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());

			// apply scale
			for (unsigned int j = 0; j < vertices.size() / VERTICES_PER_SPRITE; j++)
			{
				m_vertices[i * vertices.size() + j * VERTICES_PER_SPRITE] *= m_entities[i].extent;
				m_vertices[i * vertices.size() + j * VERTICES_PER_SPRITE] += m_entities[i].positionX;
				m_vertices[i * vertices.size() + j * VERTICES_PER_SPRITE + 1] *= m_entities[i].extent;
				m_vertices[i * vertices.size() + j * VERTICES_PER_SPRITE + 1] += m_entities[i].positionY;
			}
		}
	}

	int Bootbox::FindLastEntityByTexture(GLuint texture)
	{
		if (m_entities.empty())
			return -1;

		for (int i = (unsigned)m_entities.size() - 1; i >= 0; i--)
		{
			if (m_entities[i].texture == texture)
				return i;
		}

		return -1;
	}
}

#endif // __Bootbox__