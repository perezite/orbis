#include "Mesh.h"

#include "VideoManager.h"

namespace Video
{
	// a textured quad
	Mesh Mesh::TexturedQuad = Mesh(
		{ Vector2D(-0.5f, -0.5f), Vector2D(0.5f, -0.5f), Vector2D(-0.5f, 0.5f), Vector2D(0.5f, 0.5f) },
		{ Vector2D(0.0f, 0.0f), Vector2D(1.0f, 0.0f), Vector2D(0.0f, 1.0f), Vector2D(1.0f, 1.0f) },
		{ 0, 1, 2, 1, 3, 2 });

	// a flat quad
	Mesh Mesh::FlatQuad = Mesh(
	{ Vector2D(-0.5f, -0.5f), Vector2D(0.5f, -0.5f), Vector2D(-0.5f, 0.5f), Vector2D(0.5f, 0.5f) },
	{},
	{ 0, 1, 2, 1, 3, 2 });

	void Mesh::Initialize()
	{
		if (!m_isInitialized)
		{
			VideoManager::GetInstance()->GetRenderDevice()->AddMesh(this);
			m_isInitialized = true;
		}
	}
}