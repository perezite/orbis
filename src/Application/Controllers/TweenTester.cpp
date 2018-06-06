#include "TweenTester.h"

#include "../../Orbis/Core/TimeManager.h"
using namespace Core;

#include <iostream>

namespace Controllers
{
	void TweenTester::Start()
	{
		m_tween->SetInitial(GetParent()->GetTransform()->scale);
	}

	void TweenTester::Update()
	{
		m_tween->Update(&GetParent()->GetTransform()->scale, m_duration);
	}
}

