/* Entity.h
	class Entity : public Drawable
	{	
		virtual void update() { };

		virtual void onDraw() { };
		
		...
	}
	...
	
	std::vector<Component> m_components;
*/

void Component::draw(RenderTarget& target, RenderStates& states)
{
	foreach (component in m_components)
		component.draw(target, states);
		
	onDraw();
}
