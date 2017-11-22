#pragma once

#include "../Video/VideoManager.h"
using namespace Video;

namespace Orbis
{
	class OrbisMain
	{
	public:
		// get instance
		static OrbisMain* GetInstance();

		// destructor
		virtual ~OrbisMain() { };

		// initialize
		void Initialize();

		// run the engine
		void Run();
	};
}