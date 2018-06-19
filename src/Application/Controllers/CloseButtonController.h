#pragma once

#include "SpriteController.h"
#include "CameraController.h"

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/Texture.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Game/Transform.h"
using namespace Components;
using namespace Video;
using namespace Game;

#include <string>
#include <vector>
#include <map>

namespace Controllers
{
	class CloseButtonController : public Component
	{
	public:
		// update
		void update();
	};
}