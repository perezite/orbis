#include "TextureRenderer.h"

#include "..\Video\VideoManager.h"
using namespace Video;

#include "..\Game\Entity.h"
using namespace Game;

#include "..\Math\MathHelper.h"
using namespace Math;

#include <math.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL.h>

namespace Components
{
	void TextureRenderer::SetTexture(Texture * texture)
	{
		m_texture = texture;
	}

	void TextureRenderer::Render() 
	{ 		
		RenderDevice* renderDevice = VideoManager::GetInstance()->GetRenderDevice();
		m_texture->SetActive();
		Vector2D position = GetParent()->GetTransform()->GetPosition();

		renderDevice->BeginPrimitive(RenderMode::Quads, true);
		renderDevice->SetTextureCoordinate(Vector2D(0, 1));
		renderDevice->SetVertex2D(Vector2D(position.GetX() - 1, position.GetY() - 1));
		renderDevice->SetTextureCoordinate(Vector2D(1, 1));
		renderDevice->SetVertex2D(Vector2D(position.GetX() + 1, position.GetY() - 1));
		renderDevice->SetTextureCoordinate(Vector2D(1, 0));
		renderDevice->SetVertex2D(Vector2D(position.GetX() + 1, position.GetY() + 1));
		renderDevice->SetTextureCoordinate(Vector2D(0, 0));
		renderDevice->SetVertex2D(Vector2D(position.GetX() - 1, position.GetY() + 1));
		renderDevice->EndPrimitive();
	}
}