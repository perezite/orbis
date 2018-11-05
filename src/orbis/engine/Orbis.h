#pragma once

#include "../game/Level.h"

namespace orb 
{
	class Orbis
	{
	public:
		static Orbis* instance();

		const bool isLevelRunning() const { return m_isLevelRunning; }

		Level* getCurrentLevel() const { return m_currentLevel; }

		bool isLevelQueued() const { return m_queuedLevel ? true : false; }

		void queueLevel(void(*level)(void));

		void runLevel();

		const void close() { m_isLevelRunning = false; }

		void updateFrame();

	private:
		Orbis();

		virtual ~Orbis() { }

	private: 
		bool m_isLevelRunning;

		Level* m_currentLevel;

		void(*m_queuedLevel)(void);
	};

}