#pragma once

#include "Component.h"

#include "..\Game\Entity.h"
using namespace Game;

#include "..\Video\Texture.h"
using namespace Video;

namespace Components
{
	// A wireframe renderer (for testing)
	class TextureRenderer : public Component
	{
	public:
		// set the texture
		void SetTexture(Texture *texture);

		// update
		void Update() { };

		// render
		void Render();

	private:
		// the texture
		Texture* m_texture1;

		// temp
		GLuint m_textureId;
	};
}