#pragma once

namespace orb
{
	namespace inspectors
	{
		class Inspector
		{
		public:
			// start
			virtual void start() { };

			// update
			virtual void update() { };

			// render
			virtual void renderDebug() { };


		private:
		};		
	}
}