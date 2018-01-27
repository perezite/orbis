#pragma once

#include "Renderer.h"

#include "../Video/Texture.h"
#include "../Game/Transform.h"
using namespace Video;
using namespace Game;

#include <vector>

namespace Components
{
	// a renderer which renders a particle system
	class ParticleRenderer : public Renderer
	{
	public:
		// ctor
		ParticleRenderer(Texture* texture) : m_texture(texture)
		{}

		// start
		void Start();

		// get transforms
		std::vector<Transform>* GetTransforms() { return &m_transforms; }

	private: 
		// the texture
		Texture* m_texture;

		// a list of particle transforms 
		std::vector<Transform> m_transforms;
	};
}