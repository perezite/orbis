#pragma once

#include "SpriteController.h"
#include "CameraBehavior.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

#include <string>
#include <vector>
#include <map>

namespace app
{
	class InputModeButton : public Component 
	{
	public:
		// ctor
		InputModeButton(std::vector<std::string> textures)
			: m_textures(textures), m_spriteRenderer(NULL)
		{ }

		// start
		void start()
		{
			m_spriteRenderer = getParent()->getComponent<SpriteRenderer>();
		}

		// updateLevel
		void update();

	protected:
		// cycle through the input modes
		void cycle();

	private:
		// the textures
		std::vector<std::string> m_textures;

		// initial transforms of the entites
		std::map<Entity*, Transform> m_initialTransforms;

		// the sprite renderer
		SpriteRenderer* m_spriteRenderer;
	};
}