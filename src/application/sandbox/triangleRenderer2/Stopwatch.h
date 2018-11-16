#pragma once

#include <SDL2/SDL.h>

namespace sb
{
	namespace triangleRenderer2
	{
		class Stopwatch
		{
		public:
			Stopwatch();

			float getElapsedMs();

			float getElapsedSeconds();

		private:
			unsigned long m_startTicks; 
		};
	}
}