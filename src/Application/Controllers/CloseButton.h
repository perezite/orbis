#pragma once

#include "SpriteController.h"
#include "CameraBehavior.h"

#include "../../Orbis/Components/Component.h"
#include "../../Orbis/Components/SpriteRenderer.h"
#include "../../Orbis/Video/Texture.h"
#include "../../Orbis/Game/Entity.h"
#include "../../Orbis/Game/Transform.h"
using namespace orb;

#include <string>
#include <vector>
#include <map>

namespace app
{
	class CloseButton : public Component
	{
	public:
		// update
		void update();
	};
}