#include "WireframeRenderer.h"

#include "..\Video\VideoManager.h"
using namespace Video;

#include "..\Game\Entity.h"
using namespace Game;

#include "..\Math\MathHelper.h"
using namespace Math;

#include <math.h>

namespace Components
{
	void TestRenderer::Update() { }

	void TestRenderer::Render()
	{
		Vector2D vertices[4];
		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();
		Entity *entity = GetParent();
		Vector2D position = entity->GetTransform()->GetPosition();
		float horizontalExtent = 0.1f * entity->GetTransform()->GetScale().GetX();
		float verticalExtent = 0.1f * entity->GetTransform()->GetScale().GetY();
	
		// compute position
		vertices[0] = Vector2D(-horizontalExtent, -verticalExtent);
		vertices[1] = Vector2D(+horizontalExtent, -verticalExtent);
		vertices[2] = Vector2D(+horizontalExtent, +verticalExtent);
		vertices[3] = Vector2D(-horizontalExtent, +verticalExtent);

		// rotate vertices
		float alpha = entity->GetTransform()->GetRotation();
		for (int i = 0; i < 4; i++)
		{
			Vector2D vertex = vertices[i];

			float x = vertex.GetX() * cos(alpha) - vertex.GetY() * sin(alpha);
			float y = vertex.GetX() * sin(alpha) + vertex.GetY() * cos(alpha);
			vertices[i] = Vector2D(x, y);
		}

		// move to position
		vertices[0] = vertices[0] + entity->GetTransform()->GetPosition();
		vertices[1] = vertices[1] + entity->GetTransform()->GetPosition();
		vertices[2] = vertices[2] + entity->GetTransform()->GetPosition();
		vertices[3] = vertices[3] + entity->GetTransform()->GetPosition();

		// render
		renderDevice->BeginPrimitive(RenderMode::LineLoop);
		renderDevice->SetVertex2D(vertices[0]);
		renderDevice->SetVertex2D(vertices[1]);
		renderDevice->SetVertex2D(vertices[2]);
		renderDevice->SetVertex2D(vertices[3]);
		renderDevice->EndPrimitive();
	}
}