#include "Matrix3.h"

#include <math.h>

namespace Math
{
	Matrix3 Matrix3::Rotation2D(float rad)
	{
		return Matrix3(cosf(rad), -sinf(rad), 0.0f,
			sinf(rad), cosf(rad), 0.0f,
			0.0f, 0.0f, 1.0f);
	}

	Matrix3::Matrix3(float m00, float m01, float m02,
		float m10, float m11, float m12, 
		float m20, float m21, float m22)
	{
		m_values[0] = m00; m_values[1] = m01; m_values[2] = m02; 
		m_values[3] = m10; m_values[4] = m11; m_values[5] = m12; 
		m_values[6] = m20; m_values[7] = m21; m_values[8] = m22; 
	}

	Matrix3::Matrix3()
	{
		m_values[0] = 1.0f; m_values[1] = 0.0f; m_values[2] = 0.0f; 
		m_values[3] = 0.0f; m_values[4] = 1.0f; m_values[5] = 0.0f; 
		m_values[6] = 0.0f; m_values[7] = 0.0f; m_values[8] = 1.0f; 
	}

	const Matrix3 Matrix3::Transposed() const
	{
		Matrix3 result;

		for (unsigned int row = 0; row < 3; row++)
		{
			for (unsigned int col = 0; col < 3; col++)
			{
				float value = this->GetValue(row, col);
				result.SetValue(col, row, value);
			}
		}

		return result;
	}

	void Matrix3::Rotate2D(float rad)
	{
		*this *= Rotation2D(rad);
	}

	void Matrix3::Translate2D(Vector2D trans)
	{
		*this *= Matrix3(1.0f, 0.0f, trans.GetX(),
			0.0f, 1.0f,  trans.GetY(),
			0.0f, 0.0f, 1.0f);
	}

	void Matrix3::Scale2D(Vector2D scale)
	{
		*this *= Matrix3(scale.GetX(), 0.0f, 0.0f,
			0.0f, scale.GetY(), 0.0f,
			0.0f, 0.0f, 1.0f);
	}

	Matrix3 Matrix3::operator*(const Matrix3 & other) const
	{
		Matrix3 result;
		for (unsigned int row = 0; row < 3; row++) {
			for (unsigned int col = 0; col < 3; col++) {
				float sum = 0.0f;
				for (unsigned int i = 0; i < 3; i++)
					sum += GetValue(row, i) * other.GetValue(i, col);
				result.SetValue(row, col, sum);
			}
		}

		return result;
	}

	const Matrix3& Matrix3::operator*=(const Matrix3 & other)
	{
		Matrix3 result = *this * other;
		*this = result;
		return *this;
	}

	Vector2D Matrix3::operator*(const Vector2D & vec) const
	{
		float x = this->GetValue(0, 0) * vec.GetX() + this->GetValue(0, 1) * vec.GetY() + this->GetValue(0, 2);
		float y = this->GetValue(1, 0) * vec.GetX() + this->GetValue(1, 1) * vec.GetY() + this->GetValue(1, 2);
		return Vector2D(x, y);
	}

}
