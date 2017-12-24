#include "Bootbox.h"

#ifdef __SANDBOX__

#include "Helper.h"

#include "../../Base/Math/MathHelper.h"
#include "../../Orbis/Core/TimeManager.h"
#include "../../Orbis/Video/VideoManager_v2.h"
#include "../../Orbis/Video/Mesh_v2.h"
using namespace Math;
using namespace Core;
using namespace Video;

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
	std::vector<Entity_v2> Bootbox::m_entities;
	const int Bootbox::NUM_SPRITES = 1000;
	const int Bootbox::VERTICES_PER_SPRITE = 4;
	const int Bootbox::INDICES_PER_SPRITE = 6;
	const float Bootbox::MIN_BLOCK_EXTENT = 0.01f;
	const float Bootbox::MAX_BLOCK_EXTENT = 0.05f;

	void Bootbox::Run()
	{
		srand(42);

		TimeManager::GetInstance()->Reset();
		VideoManager_v2::GetInstance()->Initialize();
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

			UpdateEntities();

			VideoManager_v2::GetInstance()->ClearScreen();
			VideoManager_v2::GetInstance()->GetRenderDevice()->Render(Helper::GetShaderProgramHandle(), m_samplerHandle, m_positionHandle, m_texCoordHandle, m_vertices, m_indices, m_entities);
			VideoManager_v2::GetInstance()->SwapBuffers();

			Helper::LogPerformance();
		}

		Helper::Close();
	}

	void Bootbox::InitGL()
	{
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
		const std::vector<GLushort>* quadIndices = Mesh_v2::GetTexturedQuad()->GetIndices();

		m_indices.clear();
		m_indices.reserve(NUM_SPRITES * quadIndices->size());
		for (int i = 0; i < NUM_SPRITES; i++)
		{
			m_indices.insert(m_indices.end(), quadIndices->begin(), quadIndices->end());

			// compute offset for inserted indices
			for (unsigned int j = 0; j < quadIndices->size(); j++)
				m_indices[i * quadIndices->size() + j] += VERTICES_PER_SPRITE * i;
		}
	}

	void Bootbox::InitEntities()
	{
		for (unsigned int i = 0; i < NUM_SPRITES; i++)
		{
			Entity_v2 entity;

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