#include "TweenTester.h"

#include "../../Orbis/Core/TimeManager.h"
using namespace Core;

#include <iostream>

namespace Controllers
{
	void TweenTester::Start()
	{
		m_initialScale = GetParent()->GetTransform()->scale;
	}

	void TweenTester::Update()
	{
		m_elapsed += TimeManager::GetInstance()->GetDeltaSeconds();
		float t = m_elapsed / m_duration;

		if (t <= 1.0f) 
		{
			float factor = m_tween->GetCurve()->GetValue(t).y;

			Vector2D currentScale = m_initialScale * factor;
			GetParent()->GetTransform()->scale = currentScale;
		}
	}
}

