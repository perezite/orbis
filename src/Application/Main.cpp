#include <iostream>

#include "../orbis/entities/Shape.h"
#include "../orbis/Engine/Orbis.h"
#include "../orbis/core/Error.h"

void run()
{
	orb::Shape shape(orb::PrimitiveType::Triangles, 3);
	shape[0] = orb::Vertex(orb::Vector2f(-1, -1), orb::Color(255, 0, 0));
	shape[1] = orb::Vertex(orb::Vector2f(1, -1), orb::Color(0, 255, 0));
	shape[2] = orb::Vertex(orb::Vector2f(0, 1), orb::Color(0, 0, 255));

	orb::Orbis* orbis = orb::Orbis::instance();
	while (!orbis->isClosing()) {
		orbis->updateFrame();
	}
}

int main(int argc, char* args[])
{
	run();
}
