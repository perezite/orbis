#pragma once

#include "Level.h"

namespace Scene
{
	class LevelManager
	{
	public:
		// constructor
		LevelManager();

		// destructor
		virtual ~LevelManager();

		// queue level
		void QueueLevel(Level *level);

		// update
		void Update();

	protected:
		// queue next level
		void ApplyQueuedLevel();

	private:
		// current level
		Level* m_currentLevel;

		// queued level
		Level* m_queuedLevel;
	};
}
