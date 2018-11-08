// Details Bootstrapping Stufe 2: Orbis mit Levels
typedef void (*Level)();

class Orbis
{
public:
	static Orbis& instance() 
	{ 
		ORB_ASSERT(m_instance != NULL, "Please create an instance of the Orbis class before calling any orbis specific functions or constructors")
		return (*m_instance); 
	}

	Orbis(Level level) : m_instance()
	{
		ORB_ASSERT(m_instance == NULL, "Only one instance of the orbis class can be created!");
		m_instance = this;
		queueLevel(level);
	};

	void queueLevel(Level level) { m_queueLevel = level; }

	bool isLevelRunning() { m_queuedLevel = NULL; }

	bool hasLevel() { return m_queuedLevel != NULL; }

	void updateLevel()
	{
		...
	}
private:
	Level m_queueLevel;
	
	static Orbis* m_instance = NULL;
}	

// details Bootstrapping Stufe 2: Orbis Style Actors
class Actor : public Transformable
{
public:
	void update(Orbis& orbis) {
		for_each(actor in m_actors)
			actor.update(orbis);
		
		for_each (component in m_components) 
			component.update(orbis);
	}			
	
	void draw(Window& window, Transform* parentTransform)
	{
		Transform hierarchicalTransform = transform;
		if (parentTransform)
			hierarchicalTransform = parentTransform * hierarchicalTransform;
		
		
	}
	
	void addComponent(Component& component);
	
	void addChild(Actor& actor);
	
private:
	std::vector<Component*> m_components;
	
	std::vector<Actor*> m_actors;
}

class Drawable
{
	virtual draw(Window& window, Transform* parentTransform = NULL); 
}

class Component : public Drawable
{
public:
	virtual void update(Orbis& orbis) { };
	
	virtual void draw(Window& window, Transform& transform) { };
}

class Shape : Component
{
public:
	void draw(Window& window, Transform* parentTransform = NULL) 
	{
		if ()
	}	
}	

class ShapeActor
{
	
}

// Bootstrapping Stufe 1: SFML-Entities
void example1()
{
	orb::Window window(400, 400, "My Title");
	
	orb::Shape triangle(3);
	triangle[0].position = orb::Vector2f(0, 0);
	triangle[1].position = orb::Vector2f(0, 1);
	triangle[2].position = orb::Vector2f(1, 0);
	
	orb::Shape particles(3 /*number of vertices per particle*/, 2 /*number of particles*/)
	particles[0].position = orb::Vector2f(0, 0);
	particles[1].position = orb::Vector2f(0, 1);
	particles[2].position = orb::Vector2f(1, 0);
	particles[3].position = orb::Vector2f(1, 1);
	particles[4].position = orb::Vector2f(1, 2);
	particles[5].position = orb::Vector2f(2, 1);
	
	while (window.isOpen()){
		window.update();
		window.clear();
		window.draw(shape);
		window.draw(particles);
		window.display();
	}
}

// Bootstrapping Stufe 2: Transformation für SFML-Style Entities
void example2()
{
	orb::Window window(400, 400, "My Title");
	
	orb::Shape triangle(3);
	triangle[0].position = orb::Vector2f(0, 0);
	triangle[1].position = orb::Vector2f(0, 1);
	triangle[2].position = orb::Vector2f(1, 0);
	triangle.setPosition(20, 30);
	
	while (window.isOpen()){
		window.update();
		window.clear();
		window.draw(shape);
		window.draw(particles);
		window.display();
	}
}

// Bootstrapping Stufe 3: Actors
void example3()
{
	orb::Orbis orbis("My title");

	orb::ShapeActor arm(4);
	arm.getDrawable().setPosition(10, 10);		
	arm.addComponent(Talker("Talking text"));					// this text is shown every frame update
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
	
	while (window.isOpen()){
		window.update();
		window.clear();
		window.draw(shape);
		window.draw(particles);
		window.display();
	}
}

// Bootstrapping Stufe 3: Level
void example4a(orb::Orbis& orbis)
{
	orb::ShapeActor shape(3);
	shape[0].position = orb::Vector2f(0, 0);
	shape[1].position = orb::Vector2f(0, 1);
	shape[2].position = orb::Vector2f(1, 0);
	shape.setPosition(20, 30);
	shape.getDrawable().setPosition(10, 20);					// relative transformation
	shape.addComponent(Talker("My text"));						// this component will display the text "My text" each frame
	orbis.queueLevel(level2);
	
	while (orbis.isLevelRunning())
		orbis.updateLevel();
}

void example4b(orb::Orbis& orbis)
{	
	std::cout << "This text is shown once in level 2, before the application closes"
	orbis.queueLevel(NULL);										// this line can also be omitted in this case
}

void example4()
{
	orb::Orbis orbis(level1);
	while(orbis.hasLevel())
		orbis.runLevel();
	
	std::cin.get();
}

void main() 
{
	example1();
	example2();
	example3();
	example4();
}