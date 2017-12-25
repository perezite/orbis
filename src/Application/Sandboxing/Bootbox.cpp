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
using namespace Components;

#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>
#include <algorithm>

namespace Sandboxing
{
	Camera_v2* Bootbox::m_camera;
	Shader_v2* Bootbox::m_shader;
	std::vector<Texture*> Bootbox::m_textures;
	std::vector<Entity_v2> Bootbox::m_entities;
	const int Bootbox::NUM_SPRITES = 1000;
	const float Bootbox::MIN_BLOCK_SCALE = 0.01f;
	const float Bootbox::MAX_BLOCK_SCALE = 0.05f;

	void Bootbox::Run()
	{
		srand(42);

		TimeManager::GetInstance()->Reset();
		VideoManager_v2* videoManager = VideoManager_v2::GetInstance();
		videoManager->Initialize();
		Init();

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
			VideoManager_v2::GetInstance()->GetRenderDevice()->Render(m_entities);
			VideoManager_v2::GetInstance()->SwapBuffers();

			Helper::LogPerformance();
		}

		Helper::Close();
	}

	void Bootbox::Init()
	{
		m_camera = Camera_v2::GetInstance();
		m_shader = new Shader_v2("Shaders/Diffuse_v2.vs", "Shaders/Diffuse_v2.frag");

		// init data
		InitTextures();
		InitEntities();
		InitIndexArray();
	}

	void Bootbox::InitIndexArray()
	{
		std::vector<GLushort>& indexArray = VideoManager_v2::GetInstance()->GetIndexArray();

		for (unsigned int i = 0; i < m_entities.size(); i++)
		{
			Video::Mesh_v2* mesh = m_entities[i].mesh;
			const std::vector<GLushort>* MeshIndices = mesh->GetIndices();

			indexArray.insert(indexArray.end(), MeshIndices->begin(), MeshIndices->end());

			// compute offset for inserted indices
			for (unsigned int j = 0; j < MeshIndices->size(); j++)
				indexArray[i * MeshIndices->size() + j] += mesh->GetNumVertices() * i;
		}
	}

	void Bootbox::InitEntities()
	{
		for (unsigned int i = 0; i < NUM_SPRITES; i++)
		{
			Entity_v2 entity;
			entity.texture = m_textures[rand() % m_textures.size()];
			entity.shader = m_shader;
			entity.mesh = Mesh_v2::GetTexturedQuad();
			float scale = MIN_BLOCK_SCALE + (MAX_BLOCK_SCALE - MIN_BLOCK_SCALE) * MathHelper::GetRandom();
			entity.transform.scale = Vector2D(scale, scale);
			entity.transform.position = Vector2D(MathHelper::GetRandom() * 2.0f - 1.0f, MathHelper::GetRandom() * 2.0f - 1.0f);
			entity.isGrowing = rand() % 2 == 0 ? true : false;

			AddEntity(&entity);
		}
	}

	void Bootbox::InitTextures()
	{
		m_textures.push_back(new Texture("Textures/BlackBlock.png", true));
		m_textures.push_back(new Texture("Textures/BlueBlock.png", true));
		m_textures.push_back(new Texture("Textures/CyanBlock.png", true));
		m_textures.push_back(new Texture("Textures/GreenBlock.png", true));
		m_textures.push_back(new Texture("Textures/GreyBlock.png", true));
		m_textures.push_back(new Texture("Textures/OrangeBlock.png", true));
		m_textures.push_back(new Texture("Textures/PurpleBlock.png", true));
		m_textures.push_back(new Texture("Textures/RedBlock.png", true));
		m_textures.push_back(new Texture("Textures/VioletBlock.png", true));
		m_textures.push_back(new Texture("Textures/YellowBlock.png", true));
	}

	void Bootbox::UpdateEntities()
	{
		float dt = TimeManager::GetInstance()->GetDeltaSeconds();
		for (unsigned int i = 0; i < m_entities.size(); i++)
		{
			float deltaScale = m_entities[i].isGrowing ? dt * 0.01f : dt * -0.01f;
			m_entities[i].transform.scale += Vector2D(deltaScale, deltaScale);

			if (m_entities[i].transform.scale.GetX() < MIN_BLOCK_SCALE)
				m_entities[i].isGrowing = true;

			if (m_entities[i].transform.scale.GetX() > MAX_BLOCK_SCALE)
				m_entities[i].isGrowing = false;
		}
	}

	void Bootbox::AddEntity(Entity_v2* entity)
	{
		// insert batched by texture
		int lastIndex = FindIndexOfLastBatchEntity(entity);
		int insertIndex = lastIndex >= 0 ? lastIndex + 1 : m_entities.size();
		m_entities.insert(m_entities.begin() + insertIndex, *entity);
	}

	int Bootbox::FindIndexOfLastBatchEntity(Entity_v2* entity)
	{
		if (m_entities.empty())
			return -1;

		for (int i = (unsigned)m_entities.size() - 1; i >= 0; i--)
		{
			if (m_entities[i].texture == entity->texture && m_entities[i].shader == entity->shader)
				return i;
		}

		return -1;
	}

	void Bootbox::Close()
	{
		if (m_shader)
			delete m_shader;
	}
}

#endif // __Bootbox__