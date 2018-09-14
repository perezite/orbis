#include "TweenTester.h"

#include "../../Orbis/Orbis.h"
using namespace orb::core;

#include <iostream>

namespace controllers
{
	void TweenTester::start()
	{
		m_tween->setInitial(getParent()->getTransform()->scale);
	}

	void TweenTester::update()
	{
		m_tween->update(&getParent()->getTransform()->scale, m_duration);
	}
}

