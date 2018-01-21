#pragma once

#include "Renderer.h"

#include "../Video/Texture.h"
using namespace Video;

namespace Components
{
	// a renderer which renders a particle system
	class ParticleSystemRenderer : public Renderer
	{
	public:
		// ctor
		ParticleSystemRenderer(Texture* texture) : Renderer::Renderer(), m_texture(texture)
		{}

		// start
		void Start();

	private: 
		// the texture
		Texture* m_texture;
	};
}