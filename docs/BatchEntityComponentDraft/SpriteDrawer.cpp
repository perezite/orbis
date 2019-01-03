/* 
	class TetrominoDrawer : public Drawable 
	{ 
		...
*/

SpriteDrawer::draw(RenderTarget& target, RenderStates& states)
{
	states.transform *= transform;
	...
	
	m_sprite.draw(target, states);
}