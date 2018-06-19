#pragma once

#include "Level.h"

#include <map>

namespace Game
{
	class LevelManager
	{
	public:
		// get instance
		static LevelManager* getInstance();

		// queue level
		void QueueLevel(Level *level) { m_queuedLevel = level; }

		// get the current level
		Level* GetCurrentLevel() { return m_currentLevel; }
		
		// clear
		void clear();

		// update
		void Update();

		// render
		void render();

	protected:
		// constructor
		LevelManager();

		// switch to queued level
		void SwitchToQueuedLevel();

	private:
		// current level
		Level* m_currentLevel;

		// queued level
		Level* m_queuedLevel;
	};
}