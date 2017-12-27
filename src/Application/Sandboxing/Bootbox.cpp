#include "Bootbox.h"

#ifdef __SANDBOX__

#include "Helper.h"

#include "../../Base/Math/MathHelper.h"
#include "../../Orbis/Core/TimeManager.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Video/Mesh.h"
#include "../../Orbis/Components/NewSpriteRenderer.h"
#include "../../Orbis/Components/RectangleRenderer.h"
using namespace Math;
using namespace Core;
using namespace Video;
using namespace Components;

#include <stdio.h>
#include <time.h>
#include <string>
#include <iostream>

namespace Sandboxing
{
	std::vector<Texture*> Bootbox::m_textures;
	std::vector<Entity*> Bootbox::m_entities;
	const int Bootbox::NUM_SPRITES = 1000;
	const float Bootbox::MIN_BLOCK_SCALE = 0.01f;
	const float Bootbox::MAX_BLOCK_SCALE = 0.05f;

	void Bootbox::Run()
	{
		srand(41);

		TimeManager::GetInstance()->Reset();
		VideoManager* videoManager = VideoManager::GetInstance();
		videoManager->Initialize();
		Init();
		StartEntities();

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

			videoManager->ClearScreen();
			videoManager->GetRenderDevice()->Render();
			videoManager->SwapBuffers();

			Helper::LogPerformance();
		}

		Helper::Close();
	}

	void Bootbox::Init()
	{
		// init data
		InitTextures();
		InitEntities();
	}

	void Bootbox::StartEntities()
	{
		for (unsigned int i = 0; i < m_entities.size(); i++)
			m_entities[i]->Start();
	}
	
	void Bootbox::InitEntities()
	{
		for (unsigned int i = 0; i < NUM_SPRITES; i++)
		{
			Entity* entity = new Entity();
			static int counter = 0;
			bool hasTexture = ++counter % 2 == 0;

			float scale = MIN_BLOCK_SCALE + (MAX_BLOCK_SCALE - MIN_BLOCK_SCALE) * MathHelper::GetRandom();
			Transform trans = Transform(Vector2D(MathHelper::GetRandom() - 0.5f, MathHelper::GetRandom() - 0.5f), 0.0f, Vector2D(scale, scale));
			entity->SetTransform(trans);
	
			Texture* texture = hasTexture ? m_textures[rand() % m_textures.size()] : NULL; 
			entity->AddComponent(hasTexture ? (Renderer*)new NewSpriteRenderer(texture) : (Renderer*)new RectangleRenderer(Color(1.0f, 0.0f, 0.0f)));

			m_entities.push_back(entity);
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
		for (unsigned int i = 0; i < m_entities.size(); i++)
			m_entities[i]->Update();
	}

	void Bootbox::Close()
	{
		for (unsigned int i = 0; i < m_textures.size(); i++)
			delete m_textures[i];
		m_textures.clear();

		for (unsigned int i = 0; i < m_entities.size(); i++)
			delete m_entities[i];
		m_entities.clear();
	}
}

#endif // __Bootbox__