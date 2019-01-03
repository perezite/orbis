/*
	DrawBatch.h
	
	class DrawBatch : public RenderTarget
	{
		....
	}
*/

void DrawBatch::draw(const std::vector<Vertex>& vertices, RenderStates& states) 
{
	if (vertices.size() < m_batchThreshold) 
		addBatchedVertices(vertices, states);
	else
		m_batches[states].unbatchedVertices.push_back(vertices);
{
	
void addBatchedVertices(const std::vector<Vertex>& vertices, RenderStates& states)
{
	if (vertices.emtpy())
		return;
	
	m_batches[states].batchedVertices.push_back(vertices[0]);		// connect with previous object via degenerate triangle
	m_batches[states].batchedVertices.insert(m_batchedVertices.end(), vertices.begin(), vertices.end());
	m_batches[states].batchedVertices.push_back(vertices[vertices.size() - 1]);	// connect with next object via degenerate triangle
}

void draw(RenderTarget& target) 
{
	foreach (auto batchIter in m_batches) {
		target.draw(batchIter.second->batchedVertices, batchIter.first);
		
		foreach(auto unbatched in batchIter.second->unbatchedVertices) {
			target.draw(unbatched, batchIter->first);
		}
	}
}
