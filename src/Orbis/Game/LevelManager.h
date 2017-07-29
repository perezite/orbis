#pragma once

#include "Level.h"

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
		void QueueLevel(Level *level);

		// update
		void Heartbeat();

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