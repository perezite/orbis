#pragma once

#include "../game/Level.h"

namespace orb 
{
	class Orbis
	{
	public:
		static Orbis* instance();

		const bool isClosing() const { return m_isClosing; }

		Level* getCurrentLevel() const { return m_currentLevel; }

		const void close() { m_isClosing = true; }

		void updateFrame();

	private:
		Orbis();

		virtual ~Orbis() { }

	private: 
		bool m_isClosing;

		Level* m_currentLevel;
	};

}