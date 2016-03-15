#include "Orbis.h"

namespace Core
{
	Orbis::Orbis(int windowWidth, int windowHeight)
	{
		m_VideoSystem = new VideoSystem(windowWidth, windowHeight);
	}

	Orbis::~Orbis()
	{
		delete m_VideoSystem;
	}

	void Orbis::Run()
	{
		m_VideoSystem->Run();
	}
}