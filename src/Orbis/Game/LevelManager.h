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

		// queue level
		void QueueLevel(Level *level) { m_queuedLevel = level; }

		// get the current level
		Level* GetCurrentLevel() { return m_currentLevel; }

		// update
		void Update();

		// render
		void Render();

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