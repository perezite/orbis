#include "TweenTester.h"

#include "../../Orbis/Core/TimeManager.h"
using namespace orbis::core;

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

