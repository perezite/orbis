#include "BezierCurveTester.h"

#include "../../Orbis/Core/TimeManager.h"
using namespace Core;

#include <iostream>

namespace Controllers
{
	void BezierCurveTester::Start()
	{
		m_initialScale = GetParent()->GetTransform()->scale;
	}

	void BezierCurveTester::Update()
	{
		m_elapsed += TimeManager::GetInstance()->GetDeltaSeconds();
		float t = m_elapsed / m_duration;

		if (t <= 1.0f) 
		{
			float factor = m_curve.GetValue(t).y;

			Vector2D currentScale = m_initialScale * factor;
			GetParent()->GetTransform()->scale = currentScale;
		}
	}
}

