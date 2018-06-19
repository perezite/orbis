#pragma once

#include "CameraController.h"
#include "SpriteController.h"
#include "InputModeButtonController.h"

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Components/SpriteRenderer.h"
using namespace Components;

namespace Controllers
{
	class TransformButtonController : public Component
	{
	public:
		// ctor
		TransformButtonController(SpriteController* yellowBlock, 
			SpriteController* blueBlock, CameraController* camera, SpriteRenderer* inputModeRenderer, bool leftDirection)
			: m_yellowBlock(yellowBlock), m_blueBlock(blueBlock),
			m_camera(camera), m_inputModeSpriteRenderer(inputModeRenderer), m_positiveTransform(leftDirection)
		{
			StoreInitialTransforms();
		}

		// override
		void update();

	protected:
		// affect the selected entity
		void Affect();

		// store the initial transforms of the attached entities
		void StoreInitialTransforms();

		// store the initial transform of an attached entity
		void StoreInitialTransform(Component* component);

	private:
		// the yellow block controller
		SpriteController* m_yellowBlock;

		// the blue block controller
		SpriteController* m_blueBlock;

		// the camera controller
		CameraController* m_camera;

		// the input mode button sprite renderer
		SpriteRenderer* m_inputModeSpriteRenderer;

		// is left direction
		bool m_positiveTransform;

		// initial transforms of the attached entites
		std::map<Entity*, Transform> m_initialTransforms;
	};
}