#include "WobbleBrickEffect.h"

#include "../../Orbis/Orbis.h"
using namespace orb::core;

#include <iostream>

namespace app
{
	void WobbleBrickEffect::start()
	{
	}

	void WobbleBrickEffect::update()
	{
		getParent()->getTransform()->scale = Vector2D::One * m_tween->getValue(m_duration);
	}
}

