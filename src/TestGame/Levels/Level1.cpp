#include "Level1.h"

#include "..\..\Orbis\Game\Entity.h"
using namespace Game;

#include "..\..\Orbis\Components\SillyRenderer.h"
#include "..\..\Orbis\Components\TextureRenderer.h"
#include "..\..\Orbis\Components\Camera.h"
using namespace Components;

#include "..\Controllers\SimpleController.h"
#include "..\Controllers\\CameraController.h"
using namespace Controllers;

#include <iostream>

namespace Levels
{
	const std::string TransparentTestTexture1Path = "Textures\\TestTransparent.png";
	const std::string TransparentTestTexture2Path = "Textures\\TestTransparent2.png";

	Level1::Level1()
	{
		// assets
		m_texture1 = new Texture(TransparentTestTexture1Path);
		m_texture2 = new Texture(TransparentTestTexture2Path);	

		// camera entity
		Entity *camera = new Entity();
		camera->AddComponent(new Camera());
		camera->AddComponent(new CameraController());
		camera->GetTransform()->SetScale(Vector2D(8.0f, 4.0f));
		this->AddEntity(camera);

		// entity 1
		Entity *entity1 = new Entity();
		entity1->GetTransform()->SetScale(Vector2D(0.5f, 0.5f));
		entity1->AddComponent(new SillyRenderer());
		entity1->AddComponent(new SimpleController());
		this->AddEntity(entity1);

		// entity 2
		Entity *entity2 = new Entity();
		entity2->GetTransform()->SetPosition(Vector2D(1.0f, 2.0f));
		TextureRenderer* textureRenderer = new TextureRenderer();
		textureRenderer->SetTexture(m_texture1);
		entity2->AddComponent(textureRenderer);
		this->AddEntity(entity2);

		// entity 3
		Entity *entity3 = new Entity();
		entity3->GetTransform()->SetPosition(Vector2D(-1.0f, -1.0f));
		TextureRenderer* textureRenderer2 = new TextureRenderer();
		textureRenderer2->SetTexture(m_texture2);
		entity3->AddComponent(textureRenderer2);
		this->AddEntity(entity3);
	}

	Level1::~Level1()
	{
		delete m_texture1;
	}
}