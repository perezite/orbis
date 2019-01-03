/* 
	class TetrominoDrawer : public Drawable 
	{ 
		...
*/

TetrominoDrawer::draw(RenderTarget& target, RenderStates& states)
{
	states.transform *= transform;
	...
	
	for (std::size_t i = 0; i < m_stoneSprites.size(); i++) {
		currentStates = states;
		currentStates.transfrom *= m_stoneSprites[i].transform;
		m_stoneSprites[i].draw(target, currentStates);
	}
	...		
}