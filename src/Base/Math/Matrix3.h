#pragma once

#include "Vector2D.h"

namespace Math
{
	class Matrix3 
	{
	public:
		// get eye matrix
		static const Matrix3& GetEye();

	public:
		// get a 2d rotation
		static Matrix3 Rotation2D(float radians);

		// ctor
		Matrix3(float m00, float m01, float m02,
			float m10, float m11, float m12, 
			float m20, float m21, float m22);

		// ctor - sets the identity matrix
		Matrix3();

		// get value at given row/column
		float GetValue(int row, int column) const { return m_values[row * 3 + column]; }

		// get the values as a row-by-row 16-array
		float* GetValues() { return m_values; }

		// set the value at the given row/column
		void SetValue(int row, int column, float value) { m_values[row * 3 + column] = value; }

		// get the transposed matrix
		const Matrix3 Transposed() const;

		// apply a 2D-rotation in radians
		void Rotate2D(float radians);

		// apply a 2D-translation
		void Translate2D(Vector2D trans);

		// apply a 2D-scaling
		void Scale2D(Vector2D scale);

		// multiply
		Matrix3 operator*(const Matrix3& other) const;

		// multiply
		const Matrix3& operator*=(const Matrix3 &other);

		// multiply with vector
		Vector2D operator*(const Vector2D& vec) const;

	private: 
		// the matrix values
		float m_values[9];
	};
}