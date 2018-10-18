#pragma once

#include "Level.h"

#include <map>

namespace orb
{
	class LevelManager
	{
	public:
		// get instance
		static LevelManager* getInstance();

		// queue level
		void queueLevel(Level *level) { m_queuedLevel = level; }

		// get the current level
		Level* getCurrentLevel() { return m_currentLevel; }

		// clear
		void clear();

		// update Level
		void update();

		// render
		void render();

	protected:
		// constructor
		LevelManager();

		// switch to queued level
		void switchToQueuedLevel();

	private:
		// current level
		Level* m_currentLevel;

		// queued level
		Level* m_queuedLevel;
	};
}