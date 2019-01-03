/* Scene.h
	
*/

Scene::addEntity(Entity* entity) {
	m_entites.push_back(entity);
}

Scene::draw(RenderTarget& target, RenderStates& states) 
{
	foreach (Entity* entity in m_entities) {
		entity->draw(m_drawBatch);
	}
}