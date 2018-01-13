#include "BezierCurveEditor.h"

#include "../../Base/System/EnvironmentHelper.h"
using namespace System;

#include "../../Orbis/Input/InputManager.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Core/TimeManager.h"
#include "../../Orbis/Core/LogHelper.h"
#include "../Core/DebugHelper.h"
using namespace Input;
using namespace Video;
using namespace Core;

#include <iostream>
#include <sstream>
#include <algorithm>

namespace Components
{
	const float BezierCurveEditor::MARK_EXTENT = 0.01f;
	const float BezierCurveEditor::SELECT_RADIUS = 0.05f;
	const float BezierCurveEditor::TANGENT_LENGTH = 0.18f;
	const int BezierCurveEditor::SAMPLING_DENSITY = 100;
	const int BezierCurveEditor::NUM_SAMPLES = 100;

	void BezierCurveEditor::Start()
	{
		ORBIS_RELEASE(throw Exception("Creating a bezier curve editor in release mode is not allowed"); )

		m_texture = new Texture("Textures/CoordinateSystem2.png");
		GetMaterial()->SetTexture(m_texture);
		GetMaterial()->SetShader(Shader::GetDiffuseShader());
		SetMesh(Mesh::GetTexturedQuad());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderer(this);
	}

	void BezierCurveEditor::Update()
	{
		InputManager* input = InputManager::GetInstance();

		if (input->IsTapIndexGoingDown(1))
			AddOrSelectControlPoint();

		if (input->IsTapIndexDown(1) && m_selectedControlPoint != -1)
			MoveControlPoint();

		if (input->IsTapIndexDown(3) && m_selectedControlPoint != -1)
			RotateTangent();

		if (input->IsKeyGoingDown(KeyCode::d) && m_selectedControlPoint != -1)
			DeleteSelectedControlPoint();

		if (input->IsKeyGoingDown(KeyCode::Escape))
			m_selectedControlPoint = -1;

		if (input->IsKeyGoingDown(KeyCode::c))
			CopyControlPointsToClipboard();
	}

	void BezierCurveEditor::Render()
	{
		RenderBezierCurve();

		RenderControlPoints();
	}
	
	void BezierCurveEditor::AddOrSelectControlPoint()
	{
		Vector2D tap = InputManager::GetInstance()->GetAspectCorrectedTapPosition();
		if (IsClickablePosition(tap))
		{
			m_selectedControlPoint = ComputeSelectedControlPoint(tap);

			// if no control point was selected by the tap, we add a new control point
			if (m_selectedControlPoint == -1)
				m_curve.Add(BezierPoint(tap, 0.0f));
		}
	}

	void BezierCurveEditor::MoveControlPoint()
	{
		Vector2D tap = InputManager::GetInstance()->GetAspectCorrectedTapPosition();
		if (IsClickablePosition(tap))
		{
			// clamp boundary point positions
			if (m_selectedControlPoint == 0)
				tap.x = -0.5f;
			if (m_selectedControlPoint == m_curve.GetLength() - 1)
				tap.x = 0.5f;

			// move
			m_curve.Move(m_selectedControlPoint, tap);
		}
	}

	void BezierCurveEditor::RotateTangent()
	{
		Vector2D tap = InputManager::GetInstance()->GetAspectCorrectedTapPosition();
		Vector2D ctrlPoint = m_curve.Get(m_selectedControlPoint).pos;
		float tangent;
		if (tap.x > ctrlPoint.x)
			tangent = (tap.y - ctrlPoint.y) / (tap.x - ctrlPoint.x);
		if (tap.x <= ctrlPoint.x)
			tangent = (ctrlPoint.y - tap.y) / (ctrlPoint.x - tap.x);

		m_curve.Set(m_selectedControlPoint, BezierPoint(ctrlPoint, tangent));
	}

	void BezierCurveEditor::DeleteSelectedControlPoint()
	{
		// the boundary points cannot be deleted
		if (m_selectedControlPoint == 0 || m_selectedControlPoint == m_curve.GetLength() - 1)
			return;

		m_curve.Delete(m_selectedControlPoint);
		m_selectedControlPoint = -1;
	}

	void BezierCurveEditor::CopyControlPointsToClipboard()
	{
		// collect the string data
		BezierCurve shifted = GetShiftedBezierCurve(m_curve, Vector2D(0.5f, 0.5f));
		std::stringstream ss; ss << "{ ";
		for (unsigned int i = 0; i < shifted.GetLength(); i++)
		{
			ss << "{" << StringHelper::ToString(shifted.Get(i).tangent) << ", ";
			ss << shifted.Get(i).pos.ToString() << "}" << (i < shifted.GetLength() - 1 ? ", " : "");
		}
		ss << " }";

		// copy the data to clipboard
		EnvironmentHelper::WriteToClipboard(ss.str());
		LogHelper::LogMessage("Bezier data copied to clipboard");
	}

	unsigned int BezierCurveEditor::ComputeSelectedControlPoint(Vector2D tapPosition)
	{
		for (unsigned int i = 0; i < m_curve.GetLength(); i++)
		{
			if (IsControlPointSelected(i, tapPosition))
				return i;
		}

		return -1;
	}

	bool BezierCurveEditor::IsControlPointSelected(unsigned int controlPointIndex, Vector2D tapPosition)
	{
		Vector2D pos = m_curve.Get(controlPointIndex).pos;
		if (Vector2D::Distance(pos, tapPosition) <= SELECT_RADIUS)
			return true;

		return false;
	}

	void BezierCurveEditor::RenderBezierCurve()
	{
		if (m_curve.GetLength() < 2)
			return;

		float step = 1.0f / (float)NUM_SAMPLES;
		Vector2D last = m_curve.Get(0).pos;
		for (float t = 0; t <= 1.0f; t += step)
		{
			Vector2D current = m_curve.GetValue(t);
			VideoManager::GetInstance()->GetRenderDevice()->DrawDebugLine(last, current, Color::Black);
			last = current;
		}
	}

	void BezierCurveEditor::RenderControlPoints()
	{
		RenderDevice* rd = VideoManager::GetInstance()->GetRenderDevice();

		for (unsigned int i = 0; i < m_curve.GetLength(); i++)
		{
			Vector2D pos = m_curve.Get(i).pos;
			Rect rect(pos, MARK_EXTENT);
			bool isSelected = m_selectedControlPoint == i;
			rd->DrawDebugRect(rect, isSelected ? Color::Red : Color::Green);

			if (isSelected)
			{
				Vector2D v = Vector2D(1.0f, m_curve.Get(i).tangent).Normalized() * 0.5f * TANGENT_LENGTH;
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

	bool BezierCurveEditor::IsClickablePosition(Vector2D position)
	{
		Rect clickableRect = Rect(GetParent()->GetTransform()->position, 0.5f);
		return clickableRect.Contains(position);
	}

	bool BezierCurveEditor::IsSelectedControlPointOnBoundary()
	{
		return m_selectedControlPoint == 0 || m_selectedControlPoint == m_curve.GetLength() - 1;
	}

	BezierCurve BezierCurveEditor::GetShiftedBezierCurve(BezierCurve curve, Vector2D shift)
	{
		for (unsigned int i = 0; i < curve.GetLength(); i++)
		{
			BezierPoint point = curve.Get(i);
			point.pos += shift;
			curve.Set(i, point);
		}

		return curve;
	}
}
