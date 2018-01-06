#include "BezierCurveVisualizer.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Core/TimeManager.h"
using namespace Input;
using namespace Video;
using namespace Core;

#include <iostream>
#include <algorithm>

namespace Controllers
{
	const float BezierCurveVisualizer::MARK_EXTENT = 0.01f;
	const float BezierCurveVisualizer::SELECT_RADIUS = 0.05f;
	const float BezierCurveVisualizer::TANGENT_LENGTH = 0.1f;
	const float BezierCurveVisualizer::TANGENT_OMEGA = 1.0f;


	void BezierCurveVisualizer::Update()
	{
		InputManager* input = InputManager::GetInstance();
		TimeManager* time = TimeManager::GetInstance();
		if (input->IsTapIndexGoingDown(1))
		{
			Vector2D tap = input->GetAspectCorrectedTapPosition();
			m_selectedControlPoint = GetSelectedControlPoint(tap);
			
			// if no control point was selected by the tap, we add a new control point
			if (m_selectedControlPoint == -1)
			{
				m_controlPoints.push_back(tap);
				std::sort(m_controlPoints.begin(), m_controlPoints.end(), CompareControlPoints);
				m_tangents.push_back(0.0f);
			}
		}

		else if (input->IsTapIndexDown(3) && m_selectedControlPoint != -1)
		{
			Vector2D tap = input->GetAspectCorrectedTapPosition();

			// handle tangent rotation
			if (input->IsKeyDown(KeyCode::t))
			{
				Vector2D ctrlPoint = m_controlPoints[m_selectedControlPoint];
				if (tap.x > ctrlPoint.x)
				{
					float slope = (tap.y - ctrlPoint.y) / (tap.x - ctrlPoint.x);
					m_tangents[m_selectedControlPoint] = slope;
				}
			}
			else // handle control point translation
			{
				std::vector<Vector2D> newControlPoints = m_controlPoints;
				newControlPoints[m_selectedControlPoint] = tap;

				// only update if the translation did not change the order of the control points
				if (std::is_sorted(std::begin(newControlPoints), std::end(newControlPoints), CompareControlPoints))
					m_controlPoints = newControlPoints;
			}
		}
	}

	void BezierCurveVisualizer::Render()
	{
		RenderDevice* rd = VideoManager::GetInstance()->GetRenderDevice();

		for (unsigned int i = 1; i < m_controlPoints.size(); i++)
		{
			Vector2D current = m_controlPoints[i];
			Vector2D previous = m_controlPoints[i - 1];
			rd->DrawDebugLine(previous, current, Color::Black);
		}

		for (unsigned int i = 0; i < m_controlPoints.size(); i++)
		{
			Vector2D pos = m_controlPoints[i];
			Rect rect(pos, MARK_EXTENT);
			bool isSelected = m_selectedControlPoint == i;
			rd->DrawDebugRect(rect, isSelected ? Color::Red : Color::Green);

			if (isSelected)
			{
				Vector2D v(1.0f, m_tangents[i]);
				v = v.Normalized() * 0.5f * TANGENT_LENGTH;
				Vector2D tangentStart = pos - v;
				Vector2D tangentEnd = pos + v;
				Rect startRect(tangentStart, MARK_EXTENT);
				Rect endRect(tangentEnd, MARK_EXTENT);
				rd->DrawDebugLine(tangentStart, tangentEnd, Color::Red);
				rd->DrawDebugRect(startRect, Color::Red);
				rd->DrawDebugRect(endRect, Color::Red);
			}
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
