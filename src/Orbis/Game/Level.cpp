#include "Level.h"

#include "../Video/VideoManager.h"
#include "../Effects/EffectsManager.h"
#include "../Core/TimeManager.h"

#include "../../Base/Base.h"
using namespace base;

#include <iostream>

namespace orb
{
	Level::Level() : m_levelBuilder(new LevelBuilder())
	{ 
		m_levelBuilder->setLevel(this);
	}

	Level::~Level()
	{
		EffectsManager::getInstance()->clear();
		VideoManager::getInstance()->clear();
		MemoryUtil::clear(m_entities);
		if (m_levelBuilder)
			delete m_levelBuilder;
	}

	Entity* Level::findEntity(std::string name)
	{
		if (name == "")
			return NULL;

		for (unsigned int i = 0; i < m_entities.size(); i++)
		{
			if (m_entities[i]->getId() == name)
				return m_entities[i];
		}

		return NULL;
	}

	void Level::addEntity(Entity *entity)
	{
		// assert distinct id's
		if (entity->getId() != "")
		{
			for (unsigned int i = 0; i < m_entities.size(); i++)
			{
				if (m_entities[i]->getId() == entity->getId())
					throw Exception("Entity Id's must be unique");
			}
		}

		// add the entity
		if (entity) m_entities.push_back(entity);

	}

	void Level::startLevel()
	{
		TimeManager::instance()->reset();
		VideoManager::getInstance()->clear();
		start();
		startEntities();
		VideoManager::getInstance()->start();
	}

	void Level::updateLevel()
	{
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

		video->getWindow()->swap();
	}
}