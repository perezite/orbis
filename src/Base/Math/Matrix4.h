#pragma once

#include "Matrix3.h"

namespace Math
{
	class Matrix4 
	{
	public:
		// create a 4x4 matrix from  given values
		Matrix4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13, 
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		// create the identity matrix
		Matrix4();

		// get value at given row/column
		float GetValue(int row, int column) const { return m_values[row * 4 + column]; }

		// get the values as a row-by-row 16-array
		const float* GetValues() const { return m_values; }

		// set the value at the given row/column
		void SetValue(int row, int column, float value) { m_values[row * 4 + column] = value; }

		// create a 4x4 matrix from a 2D transform represented by a 3x3 matrix
		static Matrix4 From2DTransform(const Matrix3 &trans);

		// get the transposed
		const Matrix4 Transposed() const;

		// multiply a matrix
		Matrix4 operator*(const Matrix4 & other) const;

		// multiply a matrix
		const Matrix4 & operator*=(const Matrix4 & other);

	private:
		// the matrix values
		float m_values[16];
	};
}