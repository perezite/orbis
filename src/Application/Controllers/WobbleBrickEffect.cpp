#include "WobbleBrickEffect.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

#include <iostream>

namespace app
{
	WobbleBrickEffect::WobbleBrickEffect(std::string tween, float tweenDuration) : 
		Component::Component(), m_duration(tweenDuration)
	{
		m_tween = EffectsManager::instance()->getTween(tween);
	}

	void WobbleBrickEffect::start()
	{
	}

	void WobbleBrickEffect::update()
	{
		getParent()->getTransform()->scale = Vector2f::One * m_tween->getValue(m_duration);
	}
}

