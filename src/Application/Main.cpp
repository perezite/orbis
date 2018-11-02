#include <iostream>

#include "../orbis/video/Mesh.h"

int main(int argc, char* args[])
{
	orb::Mesh mesh(orb::PrimitiveType::Triangles, 3);
	mesh[0] = orb::Vertex(orb::Vector2f(-1, -1), orb::Color(255, 0, 0));
	mesh[1] = orb::Vertex(orb::Vector2f( 1, -1), orb::Color(0, 255, 0));
	mesh[2] = orb::Vertex(orb::Vector2f( 1,  0), orb::Color(0, 0, 255));

	// orb::Engine::instance()->run();
	/*orb::Engine()->run();			// Mal schauen, ob sogar das geht mit static Engine::operator()
	*/

	int i = 42;
}