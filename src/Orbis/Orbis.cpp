#include "Orbis.h"

#include "..\Core\Entity.h"
using namespace Core;

#include "..\Video\Renderer.h"
using namespace Video;

#include <iostream>
#include <vector>

namespace Core
{
	// test
	Entity g_testEntity;

	Orbis::Orbis(int windowWidth, int windowHeight) : 
		m_inputManager(InputManager::GetInstance()),
		m_videoManager(VideoManager::GetInstance()),
		m_defaultWindowSize(Vector2D(640, 480))
	{
		m_videoManager.SetWindowResolution((int)m_defaultWindowSize.GetX(), (int)m_defaultWindowSize.GetY());
	}

	void Orbis::Run()
	{
		// test 
		g_testEntity.AddComponent(new Renderer(&g_testEntity));

		while (m_inputManager.HasQuitEvent() == false)
		{
			m_inputManager.Update();

			// test
			if (m_inputManager.IsKeyDown(KeyCode::Left))
			{
				Transformation transformation = g_testEntity.GetTransformation();
				Vector2D position = transformation.GetPosition();
				Vector2D newPosition = Vector2D(position.GetX() - 0.01f, position.GetY());
				transformation.SetPosition(newPosition);
				g_testEntity.SetTransformation(transformation);
			}

			m_videoManager.Render(g_testEntity);
		}
	}
}