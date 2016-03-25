#pragma once

#include "..\Math\Vector2D.h"
using namespace Math;

#include "..\Input\InputManager.h"
using namespace Input;

#include "..\Video\VideoManager.h"
using namespace Video;

#include "..\Scene\Level.h"
using namespace Scene;

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

		// test
		void TestLevelInit();

		// test
		void TestEntityController();

	private:
		// default window size
		const Vector2D m_defaultWindowSize;
	
		// test
		Level *level;

		// test
		Entity *entity;
	};
}