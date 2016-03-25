#pragma once

#include "..\Math\Vector2D.h"
using namespace Math;

#include "..\Input\InputManager.h"
using namespace Input;

#include "..\Video\VideoManager.h"
using namespace Video;

namespace Core
{
	class Orbis
	{
	public:
		// Constructor
		Orbis(int windowWidth, int windowHeight);

		// Destructor
		virtual ~Orbis() { };

		// Run 
		void Run();

	protected:
		// temporary: test update
		void TestUpdate();

	private:
		// default window size
		const Vector2D m_defaultWindowSize;
	
		// the video system
		VideoManager m_videoManager;

		// the input manager
		InputManager m_inputManager;
	};
}