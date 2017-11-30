#include "Level1.h"

#include "../Controllers/CameraController.h"
#include "../Controllers/SpriteController.h"
#include "../Controllers/InputController.h"
using namespace Controllers;

#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Components/Camera.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/MathHelper.h"
using namespace Components;
using namespace Math;
using namespace Video;

namespace Levels
{
	Level1::Level1()
	{
		// textures
		Texture* coordSystemTexture = new Texture("Textures/CoordinateSystem.png");
		Texture* yellowBlockTexture = new Texture("Textures/YellowBlock.png");
		Texture* blueBlockTexture = new Texture("Textures/BlueBlock.png");
		Texture* overlayRotateYellowSpriteTex = new Texture("Textures/RotateYellowSprite.png");
		Texture* overlayTranslateBlueSpriteTex = new Texture("Textures/TranslateBlueSprite.png");
		Texture* overlayForwardTex = new Texture("Textures/OverlayForward.png");
		Texture* overlayLeftTex = new Texture("Textures/OverlayLeft.png");
		Texture* overlayRightTex = new Texture("Textures/OverlayRight.png");

		// camera entity
		Entity* camera = new Entity();
		camera->AddComponent(new Camera());
		camera->AddComponent(new CameraController());
		camera->SetTransform(Transform(Vector2D(-0.1f, -0.1f), 0.0f, Vector2D::One));
		this->AddEntity(camera);

		// coordinate system entity
		Entity* coordSystem = new Entity("Coordinate System");
		coordSystem->AddComponent(new SpriteRenderer(coordSystemTexture));
		this->AddEntity(coordSystem);

		// yellow block entity
		Entity* yellowBlock = new Entity("Yellow Brick");
		SpriteController* yellowBlockController = new SpriteController();
		yellowBlockController->SetOmega(MathHelper::GetPi());
		yellowBlock->AddComponent(yellowBlockController);
		yellowBlock->AddComponent(new SpriteRenderer(yellowBlockTexture));
		yellowBlock->SetTransform(Transform(Vector2D(0.25f, 0.1f), 0.0f, Vector2D(0.33f, 0.33f)));
		this->AddEntity(yellowBlock);

		// blue block entity
		Entity* blueBlock = new Entity("Blue Brick");
		SpriteController* blueBlockController = new SpriteController();
		blueBlockController->SetOmega(-MathHelper::GetPi() / 2.0f);
		blueBlock->AddComponent(blueBlockController);
		blueBlock->AddComponent(new SpriteRenderer(blueBlockTexture));
		blueBlock->SetTransform(Transform(Vector2D(-0.25f, -0.1f), 0.0f, Vector2D(0.15f, 0.15f)));
		this->AddEntity(blueBlock);

		// input mode overlay sprite
		Entity* inputModeOverlay = new Entity("InputModeOverlay");
		SpriteRenderer* inputModeOverlaySpriteRenderer = new SpriteRenderer(overlayRotateYellowSpriteTex, false);
		inputModeOverlay->AddComponent(inputModeOverlaySpriteRenderer);
		inputModeOverlay->SetTransform(Transform(Vector2D(0.25f * Camera::GetSize().GetX(), 0.25f * Camera::GetSize().GetY()), 0.0f, Vector2D(0.25f, 0.25f)));
		this->AddEntity(inputModeOverlay);

		// forward overlay sprite
		Entity* overlayForward = new Entity("OverlayForward");
		overlayForward->AddComponent(new SpriteRenderer(overlayForwardTex, false));
		overlayForward->SetTransform(Transform(Vector2D(-0.25f * Camera::GetSize().GetX(), 0.25f * Camera::GetSize().GetY()), 0.0f, Vector2D(0.5f, 0.5f)));
		this->AddEntity(overlayForward);

		// left overlay sprite
		Entity* overlayLeft = new Entity("OverlayLeft");
		overlayLeft->AddComponent(new SpriteRenderer(overlayLeftTex, false));
		overlayLeft->SetTransform(Transform(Vector2D(-0.25f * Camera::GetSize().GetX(), -0.25f * Camera::GetSize().GetY()), 0.0f, Vector2D(0.5f, 0.5f)));
		this->AddEntity(overlayLeft);

		// right overlay sprite
		Entity* overlayRight = new Entity("OverlayRight");
		overlayRight->AddComponent(new SpriteRenderer(overlayRightTex, false));
		overlayRight->SetTransform(Transform(Vector2D(0.25f * Camera::GetSize().GetX(), -0.25f * Camera::GetSize().GetY()), 0.0f, Vector2D(0.5f, 0.5f)));
		this->AddEntity(overlayRight);

		// input entity
		Entity* overlay = new Entity("Input Controller");
		InputController* inputController = new InputController();
		inputController->SetInputModeOverlayTextures({ overlayRotateYellowSpriteTex, overlayTranslateBlueSpriteTex });
		inputController->SetInputModeOverlaySpriteRenderer(inputModeOverlaySpriteRenderer);
		inputController->SetYellowBlock(yellowBlockController);
		overlay->AddComponent(inputController);
		this->AddEntity(overlay);
	}
}
