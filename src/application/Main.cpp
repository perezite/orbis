#include <iostream>
#include <vector>

class Vector2f
{
public:
	Vector2f(float x_ = 0, float y_ = 0)
		: x(x_), y(y_)
	{ }

	float x; float y;
};

Vector2f operator +(const Vector2f& left, const Vector2f& right) {
	return Vector2f(left.x + right.x, left.y + right.y);
}

class Vertex
{
public:
	Vector2f position;
};

class Transform
{
public:
	static const Transform Identity;

	Transform(Vector2f position = Vector2f())
		: m_position(position)
	{ };

	Vector2f getPosition() const { return m_position; }

private:
	Vector2f m_position;
};

Transform operator *(const Transform& left, const Transform& right) {
	return Transform(left.getPosition() + right.getPosition());
}

const Transform Transform::Identity = Transform();

class Mesh
{
public:
	Mesh(std::size_t numVertices, std::size_t numElements = 1)
		: m_numElements(numElements), m_indices(numVertices * numElements), m_vertices(numVertices * numElements)
	{
		calculateIndices();
	}

	Vertex& operator[](std::size_t index) {  return m_vertices[index]; }

	std::size_t getVertexCount() const { return m_vertices.size(); }

	const std::vector<unsigned int>& getIndices() const { return m_indices; }

	void calculateIndices() {
		for (std::size_t i = 0; i < m_vertices.size(); i++)
			m_indices[i] = i;
	}			

private:
	std::size_t m_numElements;

	std::vector<unsigned int> m_indices;

	std::vector<Vertex> m_vertices;
};

struct RenderElement {
	Mesh& mesh;
	const Transform& transform;
};

class Renderer {
public:
	void draw(Mesh& mesh, const Transform& transform) {
		m_elements.push_back(RenderElement{ mesh, transform });
	}

	void display() {
		std::cout << "Begin display" << std::endl;
		for (std::size_t i = 0; i < m_elements.size(); i++) {
			std::cout << "\tBegin element" << i << std::endl;

			std::cout << "\t\tVertices: ";
			for (std::size_t j = 0; j < m_elements[i].mesh.getVertexCount(); j++) {
				std::cout << "(" << m_elements[i].mesh[j].position.x << ", " << m_elements[i].mesh[j].position.y << ") ";
			}
			std::cout << std::endl;

			std::cout << "\t\tIndices: ";
			const std::vector<unsigned int>& indices = m_elements[i].mesh.getIndices();
			for (std::size_t j = 0; j < indices.size(); j++)
				std::cout << indices[j] << " ";
			std::cout << std::endl;

			std::cout << "\t\tTransform position: (" << m_elements[i].transform.getPosition().x << ", " << m_elements[i].transform.getPosition().y << ")" << std::endl;

			std::cout << "\tEnd element " << i << std::endl;
		}
		std::cout << "End display" << std::endl;

		m_elements.clear();
	}

private:
	std::vector<RenderElement> m_elements;
};

class Window
{
public:
	Window(unsigned int width, unsigned int height, std::string title) : m_title(title) {}

	bool isOpen() const { return true; }

	void clear() { }

	void draw(Mesh& mesh, const Transform& transform) {
		m_renderer.draw(mesh, transform);
	}

	void display() {
		m_renderer.display();
	}

private:
	std::string m_title;

	Renderer m_renderer;
};

class Drawable
{
public:
	virtual void draw(Window& window, const Transform& transform) = 0;
};

class Transformable
{
public:
	Transformable() { };
	const Transform& getTransform() { return m_transform; }

private: 
	Transform m_transform;
};

class Component : public Drawable, public Transformable
{
public:
	virtual void update() { };
};

class Shape : public Component
{
public:
	Shape(std::size_t numVertices, std::size_t numShapes = 1)
		: m_mesh(numVertices * numShapes) 
	{}

	Vertex& operator[](std::size_t index) { return m_mesh[index]; }

	void draw(Window& window, const Transform& transform = Transform::Identity)
	{
		Transform combinedTransform = transform * getTransform();
		window.draw(m_mesh, transform);
	}

private:
	Mesh m_mesh;
};

/*class Level
{
public:
void updateLevel() {
for_each(actor: m_actors)
actor.update();
}

void drawLevel(Window& window) {
for_each(actor: m_actors)
actor.draw(window);
}

private:
std::vector<Actor*> m_actors;
}

class Orbis
{
typedef void(*Level)(Orbis&);

public:
static Orbis& instance()
{
return (*m_instance);
}

Orbis(Level level) : m_instance()
{
ORB_ASSERT(m_instance == NULL, "Only one instance of the Orbis class must be constructed!");
m_instance = this;
queueLevel(level);
}

virtual ~Orbis()
{
m_instance = NULL;
}

void queueLevel(Level level) { m_queueLevel = level; }

bool isLevelRunning() { m_queuedLevel = NULL; }

bool hasLevel() { return m_queuedLevel != NULL; }

void updateLevel()
{
level.update();
}

void drawLevel(window)
{

}

private:
Level m_queueLevel;

Level level;

static Orbis* m_instance = NULL;
}

class Actor : public Transformable
{
public:
void update() {
for_each(component in m_components)
component.update(orbis);

for_each(childActor in m_childActors)
childActor.update();
}

void draw(Window& window, Transform& transform = Transform::Identity)
{
transform *= getTransform;

for_each(component in m_components)
component.draw(window, transform);

for_each(childActor in m_childActors)
childActor.draw(window, transform);
}

void addComponent(Component& component);

void addChild(Actor& actor);

private:
std::vector<Component*> m_components;

std::vector<Actor*> m_childActors;
}

class ShapeActor : Actor
{
Drawable& getDrawable() { return m_shape; }

private:
Shape m_shape;
}

// Bootstrapping Stufe 4: Automatisches Actor Management und Levels
void example4a(Orbis& orbis)
{
orb::Window window(400, 400, "My Title");
orb::Actor actor;
actor.addComponent(Talker("Talking text"));

while (orbis.isLevelRunning()) {
orbis.updateLevel();
orbis.drawLevel(window);
}
}

void example4()
{
orb::Orbis orbis(example4a);
while (orbis.hasLevel())
orbis.runLevel();
}

// Bootstrapping Stufe 3: Actors mit hierarchischen Transformationen
void example3()
{
orb::Window window(400, 400, "My Title");

orb::ShapeActor arm(4);
arm.getDrawable().setPosition(10, 10);
arm.addComponent(Talker("Talking text"));					// this text is shown every frame
person[0].position = orb::Vector2f(0, 0);
person[1].position = orb::Vector2f(2, 0);
person[2].position = orb::Vector2f(2, 0.5);
person[2].position = orb::Vector2f(0, 0.5);

orb::ShapeActor person(4);
person.addChild(arm);
person[0].position = orb::Vector2f(0, 0);
person[1].position = orb::Vector2f(1, 0);
person[2].position = orb::Vector2f(1, 1);
person[2].position = orb::Vector2f(1, 0);

while (window.isOpen()) {
window.update();
window.clear();
person.update();
person.draw(window);
window.display();
}
}

// Bootstrapping Stufe 2: Transformation f�r SFML-Style Entities
void example2()

{
orb::Window window(400, 400, "My Title");

orb::Shape triangle(3);
triangle[0].position = orb::Vector2f(0, 0);
triangle[1].position = orb::Vector2f(0, 1);
triangle[2].position = orb::Vector2f(1, 0);
triangle.setPosition(20, 30);

while (window.isOpen()) {
window.update();
window.clear();
shape.draw(window);
window.display();
}
}

*/
// Bootstrapping Stufe 1: SFML-Entities
void example1()
{
	Window window(400, 400, "My Title");

	Shape triangle(3);
	triangle[0].position = Vector2f(0, 0);
	triangle[1].position = Vector2f(0, 1);
	triangle[2].position = Vector2f(1, 0);

	triangle[2];

	Shape particles(3, 2); 
	particles[0].position = Vector2f(0, 0);
	particles[1].position = Vector2f(0, 1);
	particles[2].position = Vector2f(1, 0);
	particles[3].position = Vector2f(1, 1);
	particles[4].position = Vector2f(1, 2);
	particles[5].position = Vector2f(2, 1);

	while (window.isOpen()) {
		window.clear();
		triangle.draw(window);
		particles.draw(window);
		window.display();
	}
}

int main(int argc, char* args[])
{
	example1();
	/*example2();
	example3();
	example4();*/

	return 0;
}
