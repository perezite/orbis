#include "Matrix4.h"

#include <math.h>

namespace Math
{
	Math::Matrix4::Matrix4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33)
	{
		m_values[0] = m00; m_values[1] = m01; m_values[2] = m02; m_values[3] = m03;
		m_values[4] = m10; m_values[5] = m11; m_values[6] = m12; m_values[7] = m13;
		m_values[8] = m20; m_values[9] = m21; m_values[10] = m22; m_values[11] = m23;
		m_values[12] = m30; m_values[13] = m31; m_values[14] = m32; m_values[15] = m33;
	}

	Matrix4::Matrix4()
	{
		m_values[0] = 1.0f; m_values[1] = 0.0f; m_values[2] = 0.0f; m_values[3] = 0.0f;
		m_values[4] = 0.0f; m_values[5] = 1.0f; m_values[6] = 0.0f; m_values[7] = 0.0f;
		m_values[8] = 0.0f; m_values[9] = 0.0f; m_values[10] = 1.0f; m_values[11] = 0.0f;
		m_values[12] = 0.0f; m_values[13] = 0.0f; m_values[14] = 0.0f; m_values[15] = 1.0f;
	}

	const Matrix4 Matrix4::Transposed() const
	{
		Matrix4 result;

		for (unsigned int row = 0; row < 4; row++)
		{
			for (unsigned int col = 0; col < 4; col++)
			{
				float value = this->GetValue(row, col);
				result.SetValue(col, row, value);
			}
		}

		return result;
	}

	void Matrix4::Rotate2D(float rad)
	{
		*this *= Matrix4(cosf(rad), -sinf(rad), 0.0f, 0.0f,
			sinf(rad), cosf(rad), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix4 Matrix4::operator*(const Matrix4 & other) const
	{
		Matrix4 result;
		for (unsigned int row = 0; row < 4; row++) {
			for (unsigned int col = 0; col < 4; col++) {
				float sum = 0.0f;
				for (unsigned int i = 0; i < 4; i++)
					sum += GetValue(row, i) * other.GetValue(i, col);
				result.SetValue(row, col, sum);
			}
		}

		return result;
	}

	const Matrix4& Matrix4::operator*=(const Matrix4 & other)
	{
		Matrix4 result = *this * other;
		*this = result;
		return *this;
	}
}
