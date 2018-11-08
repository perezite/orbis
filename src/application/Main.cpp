#include "../orbis/Engine/Orbis.h"
#include "../orbis/entities/Shape.h"
#include "../orbis/core/Log.h"
#include "levels/Level1.h"
#include "sandbox/RotatingTriangleSandbox.h"

int main(int argc, char* args[])
{
	// app::RotatingTriangleSandbox::run();

	orb::Shape shape(3);
	shape[0] = orb::Vertex(orb::Vector2f(-1, -1), orb::Color(255, 0, 0));
	shape[1] = orb::Vertex(orb::Vector2f(1, -1), orb::Color(0, 255, 0));
	shape[2] = orb::Vertex(orb::Vector2f(0, 1), orb::Color(0, 0, 255));

	orb::Orbis* orbis = orb::Orbis::instance();
	while (orbis->isLevelRunning()) {
		orbis->updateFrame();
	}
}
