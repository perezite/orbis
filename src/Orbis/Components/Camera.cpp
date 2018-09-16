#include "Camera.h"

#include "../Game/Transform.h"
#include "../Game/Entity.h"
#include "../Core/TimeManager.h"
#include "../Video/VideoManager.h"
using namespace orb::game;
using namespace orb::core;
using namespace orb::video;

#include "../../Base/System/Exception.h"
#include "../../Base/Math/Math.h"
using namespace base::system;
using namespace base::math;

namespace orb
{
	namespace components
	{
		Camera* Camera::m_instance = NULL;

		Camera* Camera::getInstance()
		{
			Exception::assert(m_instance != NULL, "No camera was attached in the level");

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

		Vector2D Camera::screenSpaceToCameraSpace(Vector2D v)
		{
			return Vector2D(v.x, getAspect() * v.y);
		}

		Matrix3 Camera::calcViewMatrix(TransformSpace space)
		{
			if (space == TransformSpace::Camera)
				return Matrix3::getEye();

			Transform* transform = getInstance()->getParent()->getTransform();
			Matrix3 invTransform;
			invTransform.rotate2D(-transform->rotation);
			invTransform.translate2D(-transform->position);
			return invTransform;
		}

		// reference: http://www.songho.ca/opengl/gl_projectionmatrix.html (at the bottom)
		Matrix3 Camera::calcProjectionMatrix(TransformSpace space)
		{
			Vector2D scale =
				space == TransformSpace::World ? getInstance()->getParent()->getTransform()->scale : Vector2D::One;
			Vector2D inverseScale = Vector2D(1.0f / scale.x, 1.0f / scale.y);
			Vector2D resolution = VideoManager::getInstance()->getWindow()->getResolution();
			float inverseAspect = resolution.x / resolution.y;

			Matrix3 mat(2.0f * inverseScale.x, 0.0f, 0.0f,
				0.0f, 2.0f * inverseAspect * inverseScale.y, 0.0f,
				0.0f, 0.0f, 1.0f);
			return mat;
		}

		Matrix3 Camera::calcCamMatrix(TransformSpace space)
		{
			return calcProjectionMatrix(space) * calcViewMatrix(space);
		}

		Vector2D Camera::getSize()
		{
			Vector2D scale = getInstance()->getParent()->getTransform()->scale;
			return Vector2D(scale.x, scale.y * getAspect());
		}

		float Camera::getAspect()
		{
			Vector2D resolution = VideoManager::getInstance()->getWindow()->getResolution();
			return resolution.y / resolution.x;
		}
	}
}