#include "Level.h"

#include "../Video/VideoManager.h"
#include "../Effects/EffectsManager.h"
#include "../Core/TimeManager.h"

#include "../../Base/Base.h"
using namespace base;

#include <iostream>

namespace orb
{
	Level::~Level()
	{
		EffectsManager::getInstance()->clear();
		VideoManager::getInstance()->clear();
		MemoryUtil::clear(m_entities);
	}

	Entity* Level::findEntity(std::string name)
	{
		for (unsigned int i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i]->getName() == name)
				return m_entities[i];
		}

		return NULL;
	}

	void Level::startLevel()
	{
		TimeManager::getInstance()->reset();
		VideoManager::getInstance()->clear();
		start();
		startEntities();
		VideoManager::getInstance()->start();
	}

	void Level::updateLevel()
	{
		TimeManager::getInstance()->update();
		update();
		updateEntities();
	}

	void Level::render()
	{
		VideoManager::getInstance()->getWindow()->clear();
		renderEntities();
	}

	void Level::startEntities()
	{
		for (unsigned int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->start();
		}
	}

	void Level::updateEntities()
	{
		for (unsigned int i = 0; i < m_entities.size(); i++)
		{
			m_entities[i]->update();
		}
	}

	void Level::renderEntities()
	{
		VideoManager* video = VideoManager::getInstance();

		video->getWindow()->clear();
		video->render();

		for (unsigned int i = 0; i < m_entities.size(); i++)
			m_entities[i]->renderDebug();

		video->getWindow()->swapBuffers();
	}
}