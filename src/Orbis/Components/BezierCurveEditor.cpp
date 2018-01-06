#include "BezierCurveEditor.h"

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Core/TimeManager.h"
using namespace Input;
using namespace Video;
using namespace Core;

#include <iostream>
#include <algorithm>

namespace Components
{
	const float BezierCurveEditor::MARK_EXTENT = 0.01f;
	const float BezierCurveEditor::SELECT_RADIUS = 0.05f;
	const float BezierCurveEditor::TANGENT_LENGTH = 0.18f;
	const int BezierCurveEditor::SAMPLING_DENSITY = 100;

	void BezierCurveEditor::Update()
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

		if (input->IsKeyGoingDown(KeyCode::d) && m_selectedControlPoint != -1)
		{
			m_controlPoints.erase(m_controlPoints.begin() + m_selectedControlPoint);
			m_tangents.erase(m_tangents.begin() + m_selectedControlPoint);
			m_selectedControlPoint = -1;
		}
	}

	void BezierCurveEditor::Render()
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

	unsigned int BezierCurveEditor::GetSelectedControlPoint(Vector2D tapPosition)
	{
		for (unsigned int i = 0; i < m_controlPoints.size(); i++)
		{
			if (IsControlPointSelected(i, tapPosition))
				return i;
		}

		return -1;
	}

	bool BezierCurveEditor::IsControlPointSelected(unsigned int controlPointIndex, Vector2D tapPosition)
	{
		Vector2D controlPointPos = m_controlPoints[controlPointIndex];
		if (Vector2D::Distance(controlPointPos, tapPosition) <= SELECT_RADIUS)
			return true;

		return false;
	}

	void BezierCurveEditor::RenderBezierSegment(unsigned int endIndex)
	{
		Vector2D segmentStart = m_controlPoints[endIndex - 1];
		Vector2D segmentEnd = m_controlPoints[endIndex];
		Vector2D tangentStart = Vector2D(1, m_tangents[endIndex - 1]).Scaled(TANGENT_LENGTH);
		Vector2D tangentEnd = Vector2D(1, m_tangents[endIndex]).Scaled(TANGENT_LENGTH);
		unsigned int numSamples = std::max((int)(SAMPLING_DENSITY * Vector2D::Distance(segmentEnd, segmentStart)), SAMPLING_DENSITY);
		
		float m = (segmentEnd.y - segmentStart.y) / (segmentEnd.x - segmentStart.x);
		Vector2D last = segmentStart;
		for (unsigned int i = 1; i < numSamples; i++)
		{
			float t = (float)i / (float)(numSamples - 1);
			Vector2D p0 = segmentStart;
			Vector2D p1 = p0 + tangentStart * 0.5f;
			Vector2D p3 = segmentEnd;
			Vector2D p2 = p3 - tangentEnd * 0.5f;
			Vector2D current = Bezier(t, p0, p1, p2, p3);
			VideoManager::GetInstance()->GetRenderDevice()->DrawDebugLine(last, current, Color::Black);
			last = current;
		}
	}

	Vector2D BezierCurveEditor::Bezier(float t, Vector2D p0, Vector2D p1)
	{
		Vector2D p = p0 + (p1 - p0) * t;
		return p;
	}

	Vector2D BezierCurveEditor::Bezier(float t, Vector2D p0, Vector2D p1, Vector2D p2, Vector2D p3) 
	{
		float tt = t * t;
		float ttt = tt * t;
		float ti = (1 - t);
		float titi = ti * ti;
		float tititi = titi * ti;
		float x = tititi * p0.x + 3 * titi * t * p1.x + 3 * ti * tt * p2.x + ttt * p3.x;
		float y = tititi * p0.y + 3 * titi * t * p1.y + 3 * ti * tt * p2.y + ttt * p3.y;
		return Vector2D(x, y);
	}

}
