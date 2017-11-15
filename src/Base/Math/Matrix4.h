#pragma once

#include "Matrix3.h"

namespace Math
{
	class Matrix4 
	{
	public:
		// creates the identity matrix
		Matrix4();

		// creates a 4x4 matrix from a 2D transform represented by a 3x3 matrix
		static Matrix4 From2DTransform(const Matrix3 &trans);

		// get the transposed
		const Matrix4 Transposed() const;

		// get value at given row/column
		float GetValue(int row, int column) const { return m_values[row * 4 + column]; }

		// get the values as a row-by-row 16-array
		float* GetValues() { return m_values; }

		// set the value at the given row/column
		void SetValue(int row, int column, float value) { m_values[row * 4 + column] = value; }

	private:
		// the matrix values
		float m_values[16];
	};
}