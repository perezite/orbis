#pragma once

#include "Vector2D.h"
#include "Rect.h"

namespace Math
{
	struct Matrix3 
	{
	public:
		// get eye matrix
		static const Matrix3& getEye();

		// get a 2d rotation
		static Matrix3 rotation2D(float radians);

	public:
		// ctor
		Matrix3(float m00, float m01, float m02,
			float m10, float m11, float m12, 
			float m20, float m21, float m22);

		// ctor, identity matrix
		Matrix3();

		// apply a 2D-rotation in radians
		void rotate2D(float radians);

		// apply a 2D-translation
		void translate2D(Vector2D trans);

		// apply a 2D-scaling
		void scale2D(Vector2D scale);

		// multiply
		Matrix3 operator*(const Matrix3& other) const;

		// multiply
		const Matrix3& operator*=(const Matrix3 &other);

		// multiply with vector
		Vector2D operator*(const Vector2D& vec) const;

		// multiply with rect
		Rect operator*(const Rect& rect) const;

	protected:
		// get value at given row/column
		float getValue(int row, int column) const { return m_values[row * 3 + column]; }

		// set the value at the given row/column
		void setValue(int row, int column, float value) { m_values[row * 3 + column] = value; }

	private: 
		// the matrix values
		float m_values[9];
	};
}