#include "BezierCurveTester.h"

#include "../../Orbis/Core/TimeManager.h"
using namespace Core;

namespace Controllers
{
	void BezierCurveTester::Start()
	{
		m_start = TimeManager::GetInstance()->GetDeltaSeconds();
		m_initialScale = GetParent()->GetTransform()->scale;
	}

	void BezierCurveTester::Update()
	{
		float t = (TimeManager::GetInstance()->GetDeltaSeconds() - m_start) / m_duration;

		if (t <= 1.0f) 
		{
			float factor = m_curve->GetValue(t).y;
			Vector2D currentScale = m_initialScale * factor;
			GetParent()->GetTransform()->scale = currentScale;
		}
	}
}

