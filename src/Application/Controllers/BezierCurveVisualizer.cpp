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
	const int BezierCurveVisualizer::SAMPLING_DENSITY = 100;

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

		if (input->IsTapIndexDown(1) && m_selectedControlPoint != -1)
		{
			Vector2D tap = input->GetAspectCorrectedTapPosition();
			std::vector<Vector2D> newControlPoints = m_controlPoints;
			newControlPoints[m_selectedControlPoint] = tap;

			// only update if the translation did not change the order of the control points
			if (std::is_sorted(std::begin(newControlPoints), std::end(newControlPoints), CompareControlPoints))
				m_controlPoints = newControlPoints;
		}

		else if (input->IsTapIndexDown(3) && m_selectedControlPoint != -1)
		{
			Vector2D tap = input->GetAspectCorrectedTapPosition();
			Vector2D ctrlPoint = m_controlPoints[m_selectedControlPoint];
			if (tap.x > ctrlPoint.x)
			{
				float slope = (tap.y - ctrlPoint.y) / (tap.x - ctrlPoint.x);
				m_tangents[m_selectedControlPoint] = slope;
			}
		}
	}

	void BezierCurveVisualizer::Render()
	{
		RenderDevice* rd = VideoManager::GetInstance()->GetRenderDevice();

		for (unsigned int i = 1; i < m_controlPoints.size(); i++)
		{
			RenderBezierSegment(i);
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

	void BezierCurveVisualizer::RenderBezierSegment(unsigned int endIndex)
	{
		Vector2D segmentStart = m_controlPoints[endIndex - 1];
		Vector2D segmentEnd = m_controlPoints[endIndex];
		unsigned int numSamples = std::max((int)(SAMPLING_DENSITY * Vector2D::Distance(segmentEnd, segmentStart)), SAMPLING_DENSITY);
		
		float m = (segmentEnd.y - segmentStart.y) / (segmentEnd.x - segmentStart.x);
		Vector2D last = segmentStart;
		for (unsigned int i = 1; i < numSamples; i++)
		{
			float t = (float)i / (float)(numSamples - 1);
			Vector2D current = Bezier(t, segmentStart, segmentEnd);
			VideoManager::GetInstance()->GetRenderDevice()->DrawDebugLine(last, current, Color::Black);
			last = current;
		}
	}

	Vector2D BezierCurveVisualizer::Bezier(float t, Vector2D p0, Vector2D p1)
	{
		Vector2D p = p0 + (p1 - p0) * t;
		return p;
	}
}
