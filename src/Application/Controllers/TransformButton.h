#pragma once

#include "CameraBehavior.h"
#include "SpriteController.h"
#include "InputModeButton.h"

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Components/SpriteRenderer.h"
using namespace orb;

namespace app
{
	class TransformButton : public Component
	{
	public:
		// ctor
		TransformButton(bool leftDirection);

		// override
		void update();

	protected:
		// affect the selected entity
		void affect();

		// store the initial transforms of the attached entities
		void storeInitialTransforms();

		// store the initial transform of an attached entity
		void storeInitialTransform(Component* component);

	private:
		// the yellow block controller
		SpriteController* m_yellowBlock;

		// the blue block controller
		SpriteController* m_blueBlock;

		// the camera controller
		CameraBehavior* m_camera;

		// the input mode button sprite renderer
		SpriteRenderer* m_inputModeSpriteRenderer;

		// is left direction
		bool m_positiveTransform;

		// initial transforms of the attached entites
		std::map<Entity*, Transform> m_initialTransforms;
	};
}