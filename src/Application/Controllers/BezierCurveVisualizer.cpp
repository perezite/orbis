#include "BezierCurveVisualizer.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Video/VideoManager.h"
using namespace Input;
using namespace Video;

#include <iostream>

namespace Controllers
{
	const float BezierCurveVisualizer::MARK_EXTENT = 0.01f;
	const float BezierCurveVisualizer::SELECT_RADIUS = 0.05f;

	void BezierCurveVisualizer::Update()
	{
		InputManager* input = InputManager::GetInstance();
		if (input->IsTapGoingDown())
		{
			Vector2D position = input->GetAspectCorrectedTapPosition();
			m_selectedControlPoint = GetSelectedControlPoint(position);
			
			// if now control point was selected by the tap, we add a new control point
			if (m_selectedControlPoint == -1)
				m_controlPoints.push_back(position);
		}
	}

	void BezierCurveVisualizer::Render()
	{
		for (unsigned int i = 0; i < m_controlPoints.size(); i++)
		{
			Vector2D pos = m_controlPoints[i];
			Rect rect(pos.x - MARK_EXTENT, pos.y - MARK_EXTENT, pos.x + MARK_EXTENT, pos.y + MARK_EXTENT);
			bool isSelected = m_selectedControlPoint == i;
			VideoManager::GetInstance()->GetRenderDevice()->DrawDebugRect(rect, isSelected ? Color::Red : Color::Green);
		}
	}

	unsigned int BezierCurveVisualizer::GetSelectedControlPoint(Vector2D tapPosition)
	{
		for (unsigned int i = 0; i < m_controlPoints.size(); i++)
		{
			if (IsControlPointSelected(i, tapPosition))
				return i;
		}

		return -1;
	}

	bool BezierCurveVisualizer::IsControlPointSelected(unsigned int controlPointIndex, Vector2D tapPosition)
	{
		Vector2D controlPointPos = m_controlPoints[controlPointIndex];
		if (Vector2D::Distance(controlPointPos, tapPosition) <= SELECT_RADIUS)
			return true;

		return false;
	}

}
