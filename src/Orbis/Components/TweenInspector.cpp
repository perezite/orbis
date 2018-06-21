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

	Entity* TweenInspector::tryConstructEntity(Level* parentLevel, Tween* tween, KeyCode activationKey)
	{
		Entity* entity = NULL;

		ORBIS_DEBUG (
			entity = new Entity();
			entity->addComponent(new TweenInspector(parentLevel, tween, activationKey));
		)

		return entity;
	}

	TweenInspector::TweenInspector(Level* parentLevel, Tween* tween, KeyCode activationKey) : 
		m_tween(*tween), m_isActive(false), m_activationKey(activationKey)
	{
		ShiftCurve(m_tween.getCurve(), Vector2D(-0.5f, -0.5f));
	}

	void TweenInspector::start()
	{
		ORBIS_RELEASE(throw Exception("Creating a tween inspector in release mode is not allowed"); )

		Texture* texture = VideoManager::getInstance()->getTexture("Textures/CoordinateSystem2.png");
		getParent()->getTransform()->scale = Vector2D::Zero;
		m_renderable.getMaterial()->setTexture(texture);
		m_renderable.getMaterial()->setShader(VideoManager::getInstance()->getShader("Shaders/Diffuse.vs", "Shaders/Diffuse.frag"));
		m_renderable.setMesh(Mesh::createTexturedQuad());
		m_renderable.setTransform(getParent()->getTransform());
		VideoManager::getInstance()->getRenderDevice()->addRenderable(&m_renderable);
	}

	void TweenInspector::update()
	{
		InputManager* input = InputManager::getInstance();

		if (input->isKeyGoingDown(m_activationKey))
			toggle();

		if (m_isActive)
		{
			if (input->isTapIndexGoingDown(1))
				addOrSelectControlPoint();

			if (input->isTapIndexDown(1) && m_selectedControlPoint != -1)
				moveControlPoint();

			if (input->isTapIndexDown(3) && m_selectedControlPoint != -1)
				rotateTangent();

			if (input->isKeyGoingDown(KeyCode::d) && m_selectedControlPoint != -1)
				deleteSelectedControlPoint();

			if (input->isKeyGoingDown(KeyCode::Escape))
				m_selectedControlPoint = -1;

			if (input->isKeyGoingDown(KeyCode::s))
				saveToJsonFile();
		}
	}

	void TweenInspector::renderDebug()
	{
		if (m_isActive)
		{
			renderCurve();

			renderControlPoints();
		}
	}
	
	void TweenInspector::addOrSelectControlPoint()
	{
		Vector2D tap = InputManager::getInstance()->getTapPosition();
		if (IsClickablePosition(tap))
		{
			m_selectedControlPoint = computeSelectedControlPoint(tap);

			// if no control point was selected by the tap, we add a new control point
			if (m_selectedControlPoint == -1)
				m_tween.getCurve()->add(BezierPoint(tap, 0.0f));
		}
	}

	void TweenInspector::moveControlPoint()
	{
		Vector2D tap = InputManager::getInstance()->getTapPosition();
		if (IsClickablePosition(tap))
		{
			// clamp boundary point positions
			if (m_selectedControlPoint == 0)
				tap.x = -0.5f;
			if (m_selectedControlPoint == m_tween.getCurve()->getCount() - 1)
				tap.x = 0.5f;

			// move
			m_tween.getCurve()->move(m_selectedControlPoint, tap);
		}
	}

	void TweenInspector::rotateTangent()
	{
		Vector2D tap = InputManager::getInstance()->getTapPosition();
		Vector2D ctrlPoint = m_tween.getCurve()->get(m_selectedControlPoint).pos;
		float tangent;
		if (tap.x > ctrlPoint.x)
			tangent = (tap.y - ctrlPoint.y) / (tap.x - ctrlPoint.x);
		if (tap.x <= ctrlPoint.x)
			tangent = (ctrlPoint.y - tap.y) / (ctrlPoint.x - tap.x);

		m_tween.getCurve()->set(m_selectedControlPoint, BezierPoint(ctrlPoint, tangent));
	}

	void TweenInspector::deleteSelectedControlPoint()
	{
		// the boundary points cannot be deleted
		if (m_selectedControlPoint == 0 || m_selectedControlPoint == m_tween.getCurve()->getCount() - 1)
			return;

		m_tween.getCurve()->remove(m_selectedControlPoint);
		m_selectedControlPoint = -1;
	}

	unsigned int TweenInspector::computeSelectedControlPoint(Vector2D tapPosition)
	{
		for (unsigned int i = 0; i < m_tween.getCurve()->getCount(); i++)
		{
			if (isControlPointSelected(i, tapPosition))
				return i;
		}

		return -1;
	}

	bool TweenInspector::isControlPointSelected(unsigned int controlPointIndex, Vector2D tapPosition)
	{
		Vector2D pos = m_tween.getCurve()->get(controlPointIndex).pos;
		if (Vector2D::distance(pos, tapPosition) <= SELECT_RADIUS)
			return true;

		return false;
	}

	void TweenInspector::renderCurve()
	{
		if (m_tween.getCurve()->getCount() < 2)
			return;

		BezierCurve calcCurve = GetShiftedCurve(m_tween.getCurve(), Vector2D(0.5f, 0.5f));

		float step = 1.0f / (float)NUM_SAMPLES;
		Vector2D last = calcCurve.get(0).pos;
		for (float x = 0.0f; x <= 1.0f; x += step)
		{
			Vector2D current = calcCurve.getValue(x);
			VideoManager::getInstance()->getDebugRenderDevice()->drawDebugLine(last + Vector2D(-0.5f, -0.5f), current + Vector2D(-0.5f, -0.5f), Color::Black);
			last = current;
		}
	}

	void TweenInspector::renderControlPoints()
	{
		DebugRenderDevice* drd = VideoManager::getInstance()->getDebugRenderDevice();

		for (unsigned int i = 0; i < m_tween.getCurve()->getCount(); i++)
		{
			Vector2D pos = m_tween.getCurve()->get(i).pos;
			Rect rect(pos, MARK_EXTENT);
			bool isSelected = m_selectedControlPoint == i;
			drd->drawDebugRect(rect, isSelected ? Color::Red : Color::Green);

			if (isSelected)
			{
				Vector2D v = Vector2D(1.0f, m_tween.getCurve()->get(i).tangent).normalized() * 0.5f * TANGENT_LENGTH;
				Vector2D tangentStart = pos - v;
				Vector2D tangentEnd = pos + v;
				Rect startRect(tangentStart, MARK_EXTENT);
				Rect endRect(tangentEnd, MARK_EXTENT);
				drd->drawDebugLine(tangentStart, tangentEnd, Color::Red);
				drd->drawDebugRect(startRect, Color::Red);
				drd->drawDebugRect(endRect, Color::Red);
			}
		}
	}

	bool TweenInspector::IsClickablePosition(Vector2D position)
	{
		Rect clickableRect = Rect(getParent()->getTransform()->position, 0.5f);
		return clickableRect.contains(position);
	}

	bool TweenInspector::IsSelectedControlPointOnBoundary()
	{
		return m_selectedControlPoint == 0 || m_selectedControlPoint == m_tween.getCurve()->getCount() - 1;
	}

	void TweenInspector::ShiftCurve(BezierCurve* curve, Vector2D shift)
	{
		for (unsigned int i = 0; i < curve->getCount(); i++)
		{
			BezierPoint point = curve->get(i);
			point.pos += shift;
			curve->set(i, point);
		}
	}

	BezierCurve TweenInspector::GetShiftedCurve(BezierCurve* curve, Vector2D shift)
	{
		BezierCurve shifted = *curve;
		ShiftCurve(&shifted, shift);
		return shifted;
	}

	void TweenInspector::saveToJsonFile()
	{
		ShiftCurve(m_tween.getCurve(), Vector2D(0.5f, 0.5f));
		m_tween.saveToJsonFile();
		ShiftCurve(m_tween.getCurve(), Vector2D(-0.5f, -0.5f));
		LogHelper::logMessage("Tween data saved");
	}

	void TweenInspector::toggle()
	{
		if (m_isActive)
			getParent()->getTransform()->scale = Vector2D::Zero;
			
		else
			getParent()->getTransform()->scale = Vector2D::One;

		m_isActive = !m_isActive;
	}
}
