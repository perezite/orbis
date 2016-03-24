#include "Orbis.h"

namespace Core
{
	Orbis::Orbis(int windowWidth, int windowHeight) : 
		m_inputManager(InputManager::GetInstance())
	{
		m_VideoSystem = new VideoSystem(windowWidth, windowHeight);
	}

	Orbis::~Orbis()
	{
		delete m_VideoSystem;
	}

	void Orbis::Run()
	{
		while (m_inputManager.HasQuitEvent() == false)
		{
			m_inputManager.Update();

			m_VideoSystem->Update();
		}
	}
}