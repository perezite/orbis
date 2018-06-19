#include "TweenTester.h"

#include "../../Orbis/Core/TimeManager.h"
using namespace Core;

#include <iostream>

namespace Controllers
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

