#pragma once

#include "../Video/VideoManager.h"

namespace orb
{
	class OrbisMain
	{
	public:
		// get instance
		static OrbisMain* getInstance();

		// destructor
		virtual ~OrbisMain() { };

		// run the engine
		void run();
		
		// set a callback which is called after each rendering cycle. Can be used for testing.
		 void setOnRenderedCallback(void(*callback)(void)) { m_onRenderedCallback = callback; }

	protected:
		// singleton ctor
		OrbisMain() : m_onRenderedCallback(NULL)
		{ }

		// log the performance
		void logPerformance();

	private:
		// callback called after each redendering cycle
		void (*m_onRenderedCallback)(void);
	};
}