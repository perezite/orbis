#pragma once

namespace Math
{
	class Matrix4 
	{
	public:
		// ctor
		Matrix4(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		// ctor - sets the identity matrix
		Matrix4();

		// get value at given row/column
		float GetValue(int row, int column) const { return m_values[row * 4 + column]; }

		// get the values as a row-by-row 16-array
		float* GetValues() { return m_values; }

		// set the value at the given row/column
		void SetValue(int row, int column, float value) { m_values[row * 4 + column] = value; }

		// get the transposed matrix
		const Matrix4 Transposed() const;

		// apply a 2D-rotation in radians
		void Rotate2D(float radians);

		// multiply
		Matrix4 operator*(const Matrix4& other) const;

		// mutliply
		const Matrix4& operator*=(const Matrix4 &other);

	private: 
		// the matrix values
		float m_values[16];
	};
}