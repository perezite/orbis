/* Sprite.h:
	class Sprite : public Drawable 
	{ ...
*/

Sprite::draw(RenderTarget& target)
{
	RenderStates states;
	states.texture = m_texture;
	states.transforms *= m_transform;
	...
	target.draw(m_vertices, states);
}