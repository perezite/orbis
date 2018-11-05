#include "../orbis/Engine/Orbis.h"
#include "../orbis/entities/Shape.h"
#include "../orbis/core/Log.h"

void level2()
{
	orb::Orbis* orbis = orb::Orbis::instance();
	while (orbis->isLevelRunning())
	{
		orb::Log().message() << "level2::update" << std::endl;
		orbis->updateFrame();
	}
}

void level1()
{
	orb::Shape shape(3);
	shape[0] = orb::Vertex(orb::Vector2f(-1, -1), orb::Color(255, 0, 0));
	shape[1] = orb::Vertex(orb::Vector2f(1, -1), orb::Color(0, 255, 0));
	shape[2] = orb::Vertex(orb::Vector2f(0, 1), orb::Color(0, 0, 255));

	orb::Orbis* orbis = orb::Orbis::instance();
	while (orbis->isLevelRunning())
	{
		static int cnt = 0; cnt++;
		if (cnt > 3) 
			orbis->queueLevel(level2);

		orb::Log().message() << "level1::update" << std::endl;
		orbis->updateFrame();
	}
}

int main(int argc, char* args[])
{
	level1();
	while (orb::Orbis::instance()->isLevelQueued())
		orb::Orbis::instance()->runLevel();

	std::cin.get();
}
