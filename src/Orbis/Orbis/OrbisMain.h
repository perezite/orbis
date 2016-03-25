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
		// constructor
		OrbisMain(int windowWidth, int windowHeight);

		// ^destructor
		virtual ~OrbisMain() { };

		// queue level
		void QueueLevel(Level *level);

		// run 
		void Run();

		// test
		void TestEntityController();

	private:
		// default windosw size
		static const Vector2D m_defaultWindowSize;
	
		// test
		Level *level;

		// test
		Entity *entity;
	};
}