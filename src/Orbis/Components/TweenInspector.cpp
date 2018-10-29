#include "TweenInspector.h"

#include "../../Orbis/Video/VideoManager.h"
#include "../../Orbis/Core/TimeManager.h"
#include "../../Orbis/Core/LogUtil.h"
#include "../Core/DebugUtil.h"

#include "../../Base/Base.h"
using namespace base;

#include <iostream>
#include <sstream>
#include <algorithm>

namespace orb
{
	using namespace orb;

	const float TweenInspector::MARK_EXTENT = 0.01f;
	const float TweenInspector::SELECT_RADIUS = 0.05f;
	const float TweenInspector::TANGENT_LENGTH = 0.18f;
	const int TweenInspector::SAMPLING_DENSITY = 100;
	const int TweenInspector::NUM_SAMPLES = 100;

	TweenInspector::TweenInspector(Tween* tween, KeyCode activationKey) :
		m_tween(*tween), m_isActive(false), m_activationKey(activationKey)
	{
		ShiftSpline(m_tween.getSpline(), Vector2f(-0.5f, -0.5f));
	}

	void TweenInspector::start()
	{
		ORBIS_RELEASE(throw Exception("Creating a tween inspector in release mode is not allowed"); )

		Texture* texture = VideoManager::instance().getTexture("Textures/CoordinateSystem2.png");
		// getParent()->getTransform()->scale = Vector2f::Zero;
		 getParent()->getTransform()->scale = Vector2f(0.0f, 0.0f);
		m_renderable.getMaterial()->setTexture(texture);
		m_renderable.getMaterial()->setShader(VideoManager::instance().getShader("Shaders/Diffuse.vs", "Shaders/Diffuse.frag"));
		m_renderable.setMesh(Mesh::createTexturedQuad());
		m_renderable.setTransform(getParent()->getTransform());
		VideoManager::instance().getRenderDevice()->addRenderable(&m_renderable);
	}

	void TweenInspector::update()
	{
		InputManager* input = InputManager::instance();

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
			renderSpline();

			renderBezierPoints();
		}
	}

	void TweenInspector::addOrSelectControlPoint()
	{
		Vector2f tap = InputManager::instance()->getTapPosition();
		if (IsClickablePosition(tap))
		{
			m_selectedControlPoint = computeSelectedControlPoint(tap);

			// if no control point was selected by the tap, we add a new control point
			if (m_selectedControlPoint == -1)
				m_tween.getSpline()->add(BezierPoint(tap, 0.0f));
		}
	}

	void TweenInspector::moveControlPoint()
	{
		Vector2f tap = InputManager::instance()->getTapPosition();
		if (IsClickablePosition(tap))
		{
			// clamp boundary point positions
			if (m_selectedControlPoint == 0)
				tap.x = -0.5f;
			if (m_selectedControlPoint == m_tween.getSpline()->getCount() - 1)
				tap.x = 0.5f;

			// move
			m_tween.getSpline()->move(m_selectedControlPoint, tap);
		}
	}

	void TweenInspector::rotateTangent()
	{
		Vector2f tap = InputManager::instance()->getTapPosition();
		Vector2f ctrlPoint = m_tween.getSpline()->get(m_selectedControlPoint).pos;
		float tangent;
		if (tap.x > ctrlPoint.x)
			tangent = (tap.y - ctrlPoint.y) / (tap.x - ctrlPoint.x);
		if (tap.x <= ctrlPoint.x)
			tangent = (ctrlPoint.y - tap.y) / (ctrlPoint.x - tap.x);

		m_tween.getSpline()->set(m_selectedControlPoint, BezierPoint(ctrlPoint, tangent));
	}

	void TweenInspector::deleteSelectedControlPoint()
	{
		// the boundary points cannot be deleted
		if (m_selectedControlPoint == 0 || m_selectedControlPoint == m_tween.getSpline()->getCount() - 1)
			return;

		m_tween.getSpline()->remove(m_selectedControlPoint);
		m_selectedControlPoint = -1;
	}

	unsigned int TweenInspector::computeSelectedControlPoint(Vector2f tapPosition)
	{
		for (unsigned int i = 0; i < m_tween.getSpline()->getCount(); i++)
		{
			if (isControlPointSelected(i, tapPosition))
				return i;
		}

		return -1;
	}

	bool TweenInspector::isControlPointSelected(unsigned int controlPointIndex, Vector2f tapPosition)
	{
		Vector2f pos = m_tween.getSpline()->get(controlPointIndex).pos;
		if (Vector2f::distance(pos, tapPosition) <= SELECT_RADIUS)
			return true;

		return false;
	}

	void TweenInspector::renderSpline()
	{
		if (m_tween.getSpline()->getCount() < 2)
			return;

		Spline calcSpline = GetShiftedSpline(m_tween.getSpline(), Vector2f(0.5f, 0.5f));

		float step = 1.0f / (float)NUM_SAMPLES;
		Vector2f last = calcSpline.get(0).pos;
		for (float x = 0.0f; x <= 1.0f; x += step)
		{
			Vector2f current = calcSpline.getValue(x);
			VideoManager::instance().getDebugRenderDevice()->drawDebugLine(last + Vector2f(-0.5f, -0.5f), current + Vector2f(-0.5f, -0.5f), Color::Black);
			last = current;
		}
	}

	void TweenInspector::renderBezierPoints()
	{
		DebugRenderDevice* drd = VideoManager::instance().getDebugRenderDevice();

		for (unsigned int i = 0; i < m_tween.getSpline()->getCount(); i++)
		{
			Vector2f pos = m_tween.getSpline()->get(i).pos;
			Rect rect(pos, MARK_EXTENT);
			bool isSelected = m_selectedControlPoint == i;
			drd->drawDebugRect(rect, isSelected ? Color::Red : Color::Green);

			if (isSelected)
			{
				Vector2f v = Vector2f(1.0f, m_tween.getSpline()->get(i).tangent).normalized() * 0.5f * TANGENT_LENGTH;
				Vector2f tangentStart = pos - v;
				Vector2f tangentEnd = pos + v;
				Rect startRect(tangentStart, MARK_EXTENT);
				Rect endRect(tangentEnd, MARK_EXTENT);
				drd->drawDebugLine(tangentStart, tangentEnd, Color::Red);
				drd->drawDebugRect(startRect, Color::Red);
				drd->drawDebugRect(endRect, Color::Red);
			}
		}
	}

	bool TweenInspector::IsClickablePosition(Vector2f position)
	{
		Rect clickableRect = Rect(getParent()->getTransform()->position, 0.5f);
		return clickableRect.contains(position);
	}

	bool TweenInspector::IsSelectedControlPointOnBoundary()
	{
		return m_selectedControlPoint == 0 || m_selectedControlPoint == m_tween.getSpline()->getCount() - 1;
	}

	void TweenInspector::ShiftSpline(Spline* spline, Vector2f shift)
	{
		for (unsigned int i = 0; i < spline->getCount(); i++)
		{
			BezierPoint point = spline->get(i);
			point.pos += shift;
			spline->set(i, point);
		}
	}

	Spline TweenInspector::GetShiftedSpline(Spline* spline, Vector2f shift)
	{
		Spline shifted = *spline;
		ShiftSpline(&shifted, shift);
		return shifted;
	}

	void TweenInspector::saveToJsonFile()
	{
		ShiftSpline(m_tween.getSpline(), Vector2f(0.5f, 0.5f));
		m_tween.saveToJsonFile();
		ShiftSpline(m_tween.getSpline(), Vector2f(-0.5f, -0.5f));
		LogUtil::logMessage("Tween data saved");
	}

	void TweenInspector::toggle()
	{
		if (m_isActive)
			// getParent()->getTransform()->scale = Vector2f::Zero;
			 getParent()->getTransform()->scale = Vector2f(0.0f, 0.0f);

		else
			// getParent()->getTransform()->scale = Vector2f::One;
			getParent()->getTransform()->scale = Vector2f(1.0f, 1.0f);


		m_isActive = !m_isActive;
	}
}