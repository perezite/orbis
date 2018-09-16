#include "Level.h"

#include "../Video/VideoManager.h"
#include "../Effects/EffectsManager.h"
#include "../Core/TimeManager.h"
using namespace orb::video;
using namespace orb::effects;
using namespace orb::core;

#include "../../Base/System/MemoryUtil.h"
#include "../../Base/System/Exception.h"
using namespace base::system;

#include <iostream>

namespace orb
{
	namespace game
	{
		Level::~Level()
		{
			EffectsManager::getInstance()->clear();
			VideoManager::getInstance()->clear();
			MemoryUtil::clear(m_entities);
		}

		void Level::initialize()
		{
			TimeManager::getInstance()->reset();
			VideoManager::getInstance()->clear();
			start();
			startEntities();
			VideoManager::getInstance()->start();
		}

		void Level::update()
		{
			TimeManager::getInstance()->update();
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
}