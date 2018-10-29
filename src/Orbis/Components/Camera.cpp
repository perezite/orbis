#include "Camera.h"

#include "../Game/Transform.h"
#include "../Game/Entity.h"
#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"

#include "../../Base/Base.h"
using namespace base;

namespace orb
{
	Camera* Camera::m_instance = NULL;

	Camera* Camera::instance()
	{
		return m_instance;
	}

	Camera::Camera() : Component()
	{
		Exception::assert(m_instance == NULL, "Only one camera at a time is allowed");
		m_instance = this;
	}

	Camera::~Camera()
	{
		m_instance = NULL;
	}

	void Camera::update()
	{
		m_localCamMatrix = calcCamMatrix(TransformSpace::Camera);
		m_worldCamMatrix = calcCamMatrix(TransformSpace::World);
	}

	Vector2f Camera::screenSpaceToCameraSpace(Vector2f v)
	{
		return Vector2f(v.x, getAspect() * v.y);
	}

	Matrix3 Camera::calcViewMatrix(TransformSpace space)
	{
		if (space == TransformSpace::Camera)
			return Matrix3::getEye();

		Transform* transform = instance()->getParent()->getTransform();
		Matrix3 invTransform;
		invTransform.rotate2D(-transform->rotation);
		invTransform.translate2D(-transform->position);
		return invTransform;
	}

	// reference: http://www.songho.ca/opengl/gl_projectionmatrix.html (at the bottom)
	Matrix3 Camera::calcProjectionMatrix(TransformSpace space)
	{
		Vector2f scale =
			space == TransformSpace::World ? instance()->getParent()->getTransform()->scale : Vector2f::One;
		Vector2f inverseScale = Vector2f(1.0f / scale.x, 1.0f / scale.y);
		Vector2u resolution = VideoManager::instance().getWindow()->getResolution();
		float inverseAspect = (float)resolution.x / (float)resolution.y;

		Matrix3 mat(2.0f * inverseScale.x, 0.0f, 0.0f,
			0.0f, 2.0f * inverseAspect * inverseScale.y, 0.0f,
			0.0f, 0.0f, 1.0f);
		return mat;
	}

	const Matrix3& Camera::getCamMatrix(TransformSpace space) const
	{
		return space == TransformSpace::World ? m_worldCamMatrix : m_localCamMatrix;
	}

	Vector2f Camera::getSize()
	{
		Vector2f scale = instance()->getParent()->getTransform()->scale;
		return Vector2f(scale.x, scale.y * getAspect());
	}

	float Camera::getAspect()
	{
		Vector2u resolution = VideoManager::instance().getWindow()->getResolution();
		return (float)resolution.y / (float)resolution.x;
	}

	Matrix3 Camera::calcCamMatrix(TransformSpace space)
	{
		return calcProjectionMatrix(space) * calcViewMatrix(space);
	}
}