#pragma once

#include "Level.h"

#include <map>

namespace Game
{
	class LevelManager
	{
	public:
		// get instance
		static LevelManager* GetInstance();

		// destructor
		virtual ~LevelManager();

		// register a level
		void RegisterLevel(std::string name, Level* level) { m_levels[name] = level; }

		// queue level
		void QueueLevel(Level *level) { m_queuedLevel = level; }

		// get the current level
		Level* GetCurrentLevel() { return m_currentLevel; }

		// update
		void Update();

	protected:
		// constructor
		LevelManager();

		// switch to queued level
		void SwitchToQueuedLevel();

	private:
		// the registered levels
		std::map<std::string, Level*> m_levels;

		// current level
		Level* m_currentLevel;

		// queued level
		Level* m_queuedLevel;
	};
}