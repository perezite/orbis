#pragma once

#include "..\Input\InputManager.h"
using namespace Input;

#include "..\Video\VideoSystem.h"
using namespace Video;

namespace Core
{
	class Orbis
	{
	public:
		// Constructor
		Orbis(int windowWidth, int windowHeight);

		// Destructor
		virtual ~Orbis();

		// Run 
		void Run();

	private:
		VideoSystem *m_VideoSystem;

		InputManager m_inputManager;
	};
}