#include "Level1.h"

#include "Level2.h"
#include "LevelUtil.h"

#include "../Controllers/CameraBehavior.h"
#include "../Controllers/SpriteController.h"
#include "../Controllers/InputModeButton.h"
#include "../Controllers/TransformButton.h"
#include "../Controllers/CloseButton.h"
#include "../Controllers/LevelSwitchButtonController.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

#include <map>
#include <vector>

namespace app
{
	void Level1::start()
	{
		std::vector<std::string> inputModeTextures = { 
			"Textures/RotateYellowSprite.png", "Textures/TranslateYellowSprite.png", "Textures/TranslateBlueSprite.png", 
			"Textures/RotateCamera.png", "Textures/TranslateCamera.png", "Textures/ScaleCamera.png", "Textures/Reset.png" };

		build()->entity()->withComponent(new Camera())->withComponent(new CameraBehavior())->go();

		LevelUtil::addLevelSwitcher<Level2>(true);

		build()->entity("coordinate system")->withComponent(new SpriteRenderer("Textures/CoordinateSystem.png"))->go();

		build()->entity("yellowBlock")->withComponent(new SpriteRenderer("Textures/YellowBlock.png"))
			->withComponent(new SpriteController(MathUtil::getPi()))
			->withPosition(0.25f, 0.1f)->withScale(0.33f, 0.33f)->go();

		build()->entity("blueBlock")->withComponent(new SpriteRenderer("Textures/BlueBlock.png"))
			->withComponent(new SpriteController(-MathUtil::getPi() / 2.0f))
			->withPosition(-0.25f, -0.1f)->withScale(0.15f, 0.15f)->go();

		Camera* cam = Camera::instance();

		build()->entity("inputModeButton")->withComponent(new SpriteRenderer("Textures/RotateYellowSprite.png"))
			->withComponent(new InputModeButton(inputModeTextures))
			->withPosition(-0.25f * cam->getSize().x, 0.25f * cam->getSize().y)->withScale(0.25f, 0.25f)
			->withTransformSpace(TransformSpace::Camera)->go();

		build()->entity("leftButton")->withComponent(new SpriteRenderer("Textures/OverlayLeft.png"))
			->withComponent(new TransformButton(false))
			->withPosition(-0.25f * cam->getSize().x, -0.25f * cam->getSize().y)->withScale(0.5f, 0.5f)
			->withTransformSpace(TransformSpace::Camera)->go();

		build()->entity("rightButton")->withComponent(new SpriteRenderer("Textures/OverlayRight.png"))
			->withComponent(new TransformButton(true))
			->withPosition(0.25f * cam->getSize().x, -0.25f * cam->getSize().y)->withScale(0.5f, 0.5f)
			->withTransformSpace(TransformSpace::Camera)->go();

		build()->entity("closeButton")->withComponent(new SpriteRenderer("Textures/OverlayClose.png"))
			->withComponent(new CloseButton())
			->withPosition(0.25f * cam->getSize().x, 0.25f * cam->getSize().y)->withScale(0.25f, 0.25f)
			->withTransformSpace(TransformSpace::Camera)->go();
	}
}
