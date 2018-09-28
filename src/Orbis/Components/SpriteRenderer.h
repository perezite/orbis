#pragma once

#include "Component.h"

#include "../Video/Texture.h"
#include "../Video/Renderable.h"

namespace orb
{
	// A renderer which renders a textured quad
	class SpriteRenderer : public Component
	{
	public:
		// ctor
		SpriteRenderer(std::string assetPath);

		// start
		void start();

		// set the texture
		void setTexture(std::string path);

		// get the texture path
		 std::string getTexturePath(void) { return m_renderable.getMaterial()->getTexture()->getAssetPath(); }

		// get the texture
		 Texture* getTexture(void) { return m_renderable.getMaterial()->getTexture(); }

	private:
		// the texture
		Texture* m_texture;

		// the renderable
		Renderable m_renderable;
	};
}