#include "WobbleBrickEffect.h"

#include "../../Orbis/Orbis.h"
using namespace orb;

#include <iostream>

namespace app
{
	WobbleBrickEffect::WobbleBrickEffect(std::string tween, float tweenDuration) : 
		Component::Component(), m_duration(tweenDuration)
	{
		m_tween = EffectsManager::getInstance()->getTween(tween);
	}

	void WobbleBrickEffect::start()
	{
	}

	void WobbleBrickEffect::update()
	{
		// getParent()->getTransform()->scale = Vector2f::One * m_tween->getValue(m_duration);
		 getParent()->getTransform()->scale = Vector2f(1.0f, 1.0f) * m_tween->getValue(m_duration);
	}
}

