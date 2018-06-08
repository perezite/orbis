#include "TweenInspector.h"

#include "../../Base/System/EnvironmentHelper.h"
#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Core/TimeManager.h"
#include "../../Orbis/Core/LogHelper.h"
#include "../Core/DebugHelper.h"
using namespace System;
using namespace Video;
using namespace Core;

#include <iostream>
#include <sstream>
#include <algorithm>

namespace Components
{
	const float TweenInspector::MARK_EXTENT = 0.01f;
	const float TweenInspector::SELECT_RADIUS = 0.05f;
	const float TweenInspector::TANGENT_LENGTH = 0.18f;
	const int TweenInspector::SAMPLING_DENSITY = 100;
	const int TweenInspector::NUM_SAMPLES = 100;

	Entity* TweenInspector::TryConstructEntity(Level* parentLevel, Tween* tween, KeyCode activationKey)
	{
		Entity* entity = NULL;

		ORBIS_DEBUG (
			entity = new Entity();
			entity->AddComponent(new TweenInspector(parentLevel, tween, activationKey));
		)

		return entity;
	}

	TweenInspector::TweenInspector(Level* parentLevel, Tween* tween, KeyCode activationKey) : 
		m_tween(*tween), m_parentLevel(parentLevel), m_isActive(false), m_activationKey(activationKey)
	{
		ShiftCurve(m_tween.GetCurve(), Vector2D(-0.5f, -0.5f));
	}

	TweenInspector::~TweenInspector()
	{
		VideoManager::GetInstance()->GetRenderDevice()->DeleteRenderable(m_renderable);
		delete m_renderable;
	}

	void TweenInspector::Start()
	{
		ORBIS_RELEASE(throw Exception("Creating a tween inspector in release mode is not allowed"); )

		Texture* texture = VideoManager::GetInstance()->GetTexture("Textures/CoordinateSystem2.png");
		GetParent()->GetTransform()->scale = Vector2D::Zero;
		m_renderable = new Renderable;
		m_renderable->GetMaterial()->SetTexture(texture);
		m_renderable->GetMaterial()->SetShader(VideoManager::GetInstance()->GetShader("Shaders/Diffuse"));
		m_renderable->SetMesh(Mesh::CreateTexturedQuad());
		m_renderable->SetTransform(GetParent()->GetTransform());
		VideoManager::GetInstance()->GetRenderDevice()->AddRenderable(m_renderable);
	}

	void TweenInspector::Update()
	{
		InputManager* input = InputManager::GetInstance();

		if (input->IsKeyGoingDown(m_activationKey))
			Toggle();

		if (m_isActive)
		{
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

			if (input->IsKeyGoingDown(KeyCode::s))
				Save();
		}
	}

	void TweenInspector::RenderDebug()
	{
		if (m_isActive)
		{
			RenderCurve();

			RenderControlPoints();
		}
	}
	
	void TweenInspector::AddOrSelectControlPoint()
	{
		Vector2D tap = InputManager::GetInstance()->GetTapPosition();
		if (IsClickablePosition(tap))
		{
			m_selectedControlPoint = ComputeSelectedControlPoint(tap);

			// if no control point was selected by the tap, we add a new control point
			if (m_selectedControlPoint == -1)
				m_tween.GetCurve()->Add(BezierPoint(tap, 0.0f));
		}
	}

	void TweenInspector::MoveControlPoint()
	{
		Vector2D tap = InputManager::GetInstance()->GetTapPosition();
		if (IsClickablePosition(tap))
		{
			// clamp boundary point positions
			if (m_selectedControlPoint == 0)
				tap.x = -0.5f;
			if (m_selectedControlPoint == m_tween.GetCurve()->GetLength() - 1)
				tap.x = 0.5f;

			// move
			m_tween.GetCurve()->Move(m_selectedControlPoint, tap);
		}
	}

	void TweenInspector::RotateTangent()
	{
		Vector2D tap = InputManager::GetInstance()->GetTapPosition();
		Vector2D ctrlPoint = m_tween.GetCurve()->Get(m_selectedControlPoint).pos;
		float tangent;
		if (tap.x > ctrlPoint.x)
			tangent = (tap.y - ctrlPoint.y) / (tap.x - ctrlPoint.x);
		if (tap.x <= ctrlPoint.x)
			tangent = (ctrlPoint.y - tap.y) / (ctrlPoint.x - tap.x);

		m_tween.GetCurve()->Set(m_selectedControlPoint, BezierPoint(ctrlPoint, tangent));
	}

	void TweenInspector::DeleteSelectedControlPoint()
	{
		// the boundary points cannot be deleted
		if (m_selectedControlPoint == 0 || m_selectedControlPoint == m_tween.GetCurve()->GetLength() - 1)
			return;

		m_tween.GetCurve()->Delete(m_selectedControlPoint);
		m_selectedControlPoint = -1;
	}

	unsigned int TweenInspector::ComputeSelectedControlPoint(Vector2D tapPosition)
	{
		for (unsigned int i = 0; i < m_tween.GetCurve()->GetLength(); i++)
		{
			if (IsControlPointSelected(i, tapPosition))
				return i;
		}

		return -1;
	}

	bool TweenInspector::IsControlPointSelected(unsigned int controlPointIndex, Vector2D tapPosition)
	{
		Vector2D pos = m_tween.GetCurve()->Get(controlPointIndex).pos;
		if (Vector2D::Distance(pos, tapPosition) <= SELECT_RADIUS)
			return true;

		return false;
	}

	void TweenInspector::RenderCurve()
	{
		if (m_tween.GetCurve()->GetLength() < 2)
			return;

		BezierCurve calcCurve = GetShiftedCurve(m_tween.GetCurve(), Vector2D(0.5f, 0.5f));

		float step = 1.0f / (float)NUM_SAMPLES;
		Vector2D last = calcCurve.Get(0).pos;
		for (float x = 0.0f; x <= 1.0f; x += step)
		{
			Vector2D current = calcCurve.GetValue(x);
			VideoManager::GetInstance()->GetRenderDevice()->DrawDebugLine(last + Vector2D(-0.5f, -0.5f), current + Vector2D(-0.5f, -0.5f), Color::Black);
			last = current;
		}
	}

	void TweenInspector::RenderControlPoints()
	{
		RenderDevice* rd = VideoManager::GetInstance()->GetRenderDevice();

		for (unsigned int i = 0; i < m_tween.GetCurve()->GetLength(); i++)
		{
			Vector2D pos = m_tween.GetCurve()->Get(i).pos;
			Rect rect(pos, MARK_EXTENT);
			bool isSelected = m_selectedControlPoint == i;
			rd->DrawDebugRect(rect, isSelected ? Color::Red : Color::Green);

			if (isSelected)
			{
				Vector2D v = Vector2D(1.0f, m_tween.GetCurve()->Get(i).tangent).Normalized() * 0.5f * TANGENT_LENGTH;
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

	bool TweenInspector::IsClickablePosition(Vector2D position)
	{
		Rect clickableRect = Rect(GetParent()->GetTransform()->position, 0.5f);
		return clickableRect.Contains(position);
	}

	bool TweenInspector::IsSelectedControlPointOnBoundary()
	{
		return m_selectedControlPoint == 0 || m_selectedControlPoint == m_tween.GetCurve()->GetLength() - 1;
	}

	void TweenInspector::ShiftCurve(BezierCurve* curve, Vector2D shift)
	{
		for (unsigned int i = 0; i < curve->GetLength(); i++)
		{
			BezierPoint point = curve->Get(i);
			point.pos += shift;
			curve->Set(i, point);
		}
	}

	BezierCurve TweenInspector::GetShiftedCurve(BezierCurve* curve, Vector2D shift)
	{
		BezierCurve shifted = *curve;
		ShiftCurve(&shifted, shift);
		return shifted;
	}

	void TweenInspector::Save()
	{
		ShiftCurve(m_tween.GetCurve(), Vector2D(0.5f, 0.5f));
		m_tween.Save();
		ShiftCurve(m_tween.GetCurve(), Vector2D(-0.5f, -0.5f));
		LogHelper::LogMessage("Tween data saved");
	}

	void TweenInspector::Toggle()
	{
		if (m_isActive)
			GetParent()->GetTransform()->scale = Vector2D::Zero;
			
		else
			GetParent()->GetTransform()->scale = Vector2D::One;

		m_isActive = !m_isActive;
	}
}
