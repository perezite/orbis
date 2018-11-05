#pragma once

#include "../game/Level.h"

namespace orb 
{
	class Orbis
	{
	public:
		static Orbis* instance();

		const bool isRunning() const { return m_isRunning; }

		Level* getCurrentLevel() const { return m_currentLevel; }

		const void close() { m_isRunning = false; }

		void updateFrame();

	private:
		Orbis();

		virtual ~Orbis() { }

	private: 
		bool m_isRunning;

		Level* m_currentLevel;
	};

}