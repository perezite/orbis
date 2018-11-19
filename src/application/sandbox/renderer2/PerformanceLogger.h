#pragma once

#include "Stopwatch.h"

namespace sb
{
	namespace renderer2
	{
		class PerformanceLogger
		{
		public :
			static void log()
			{
				static Stopwatch stopwatch;
				static unsigned int frames = 0;

				float elapsed = stopwatch.getElapsedSeconds();
				frames++;
				if (elapsed > 1.0f) {
					float fps = frames / elapsed;
					SDL_Log("FPS: %f", fps);
					frames = 0;
					stopwatch.reset();
				}
			}
		};
	}
}