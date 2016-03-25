#pragma once

#include "..\Math\Vector2D.h"
using namespace Math;

#include "..\Input\InputManager.h"
using namespace Input;

#include "..\Video\VideoManager.h"
using namespace Video;

#include "..\Game\Level.h"
using namespace Game;

#undef main

namespace Orbis
{
	class OrbisMain
	{
	public:
		// Constructor
		OrbisMain(int windowWidth, int windowHeight);

		// Destructor
		virtual ~OrbisMain() { };

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