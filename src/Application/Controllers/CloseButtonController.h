#pragma once

#include "SpriteController.h"
#include "CameraController.h"

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/Texture.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Game/Transform.h"
using namespace orb::components;
using namespace orb::video;
using namespace orb::game;

#include <string>
#include <vector>
#include <map>

namespace controllers
{
	class CloseButtonController : public Component
	{
	public:
		// update
		void update();
	};
}