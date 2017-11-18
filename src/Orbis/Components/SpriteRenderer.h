#pragma once

#include "Component.h"

#include "../Video/Texture.h"
using namespace Video;

namespace Components
{
	// A renderer which renders a triangle
	class SpriteRenderer : public Component
	{
	public:
		// ctor
		SpriteRenderer(std::string textureAssetPath) { m_textureAssetPath = textureAssetPath; }

		// dtor
		~SpriteRenderer();

		// update
		void Start();

		// render
		void Render();

	private:
		// the texture asset path
		std::string m_textureAssetPath;

		// the texture
		Texture* m_texture;
	};
}