#include "TweenTester.h"

#include "../../Orbis/Core/TimeManager.h"
using namespace Core;

#include <iostream>

namespace Controllers
{
	void TweenTester::start()
	{
		m_tween->SetInitial(GetParent()->getTransform()->scale);
	}

	void TweenTester::Update()
	{
		m_tween->Update(&GetParent()->getTransform()->scale, m_duration);
	}
}

