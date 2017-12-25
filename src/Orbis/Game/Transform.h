#pragma once

#include "TransformSpace.h"

#include "../../Base/Math/Vector2D.h"
#include "../../Base/Math/Matrix4.h"
using namespace Math;

namespace Game
{
	// Represents the transformation of an Entity
	class Transform
	{
	public:
		// default constructor
		Transform() : m_position(Vector2D::Zero), m_rotation(0.0f), m_scale(Vector2D::One), m_transformSpace(TransformSpace::WorldSpace) { }

		// constructor
		Transform(Vector2D position, float rotation, Vector2D scale, const TransformSpace transformSpace = TransformSpace::WorldSpace) 
			: m_position (position), m_rotation(rotation), m_scale(scale), m_transformSpace(transformSpace) { }

		// destructor
		virtual ~Transform() { }

		// get position
		Vector2D GetPosition() const { return m_position; }

		// get rotation
		float GetRotation() const { return m_rotation; }

		// get scale
		Vector2D GetScale() const { return m_scale; }

		// get the transform space
		TransformSpace GetTransformSpace() const { return m_transformSpace; }

		// set position 
		void SetPosition(Vector2D position) { m_position = position; }

		// set rotation
		void SetRotation(float rotation) { m_rotation = rotation;  }

		// set scale
		void SetScale(Vector2D scale) { m_scale = scale; }

		// set the transform space
		void SetTransformSpace(TransformSpace space) { m_transformSpace = space; }

		// get the transformation matrix
		Matrix3 GetModelMatrix() const;

	private:
		// position
		Vector2D m_position;

		// rotation
		float m_rotation;

		// scale
		Vector2D m_scale;

		// the transform space
		TransformSpace m_transformSpace;
	};
}