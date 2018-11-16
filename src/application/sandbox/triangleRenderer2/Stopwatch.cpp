#include "Stopwatch.h"

namespace sb
{
	namespace triangleRenderer2
	{
		Stopwatch::Stopwatch()
		{
			m_startTicks = SDL_GetTicks();
		}

		float Stopwatch::getElapsedMs()
		{
			return  float(SDL_GetTicks() - m_startTicks);
		}

		float Stopwatch::getElapsedSeconds()
		{
			return getElapsedMs() / 1000.0f;
		}
	}
}