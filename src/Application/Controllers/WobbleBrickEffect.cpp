#include "WobbleBrickEffect.h"

#include "../../Orbis/Orbis.h"
using namespace orb::core;

#include <iostream>

namespace controllers
{
	void WobbleBrickEffect::start()
	{
		m_tween->setInitial(getParent()->getTransform()->scale);
	}

	void WobbleBrickEffect::update()
	{
		m_tween->update(&getParent()->getTransform()->scale, m_duration);
	}
}

