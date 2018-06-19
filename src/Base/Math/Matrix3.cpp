#include "Matrix3.h"

#include <math.h>

namespace Math
{
	const Matrix3& Matrix3::getEye()
	{
		static Matrix3 eye =
			Matrix3(1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f);

		return eye;
	}

	Matrix3 Matrix3::rotation2D(float rad)
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
		*this = getEye();
	}

	void Matrix3::rotate2D(float rad)
	{
		*this *= rotation2D(rad);
	}

	void Matrix3::translate2D(Vector2D trans)
	{
		*this *= Matrix3(1.0f, 0.0f, trans.x,
			0.0f, 1.0f,  trans.y,
			0.0f, 0.0f, 1.0f);
	}

	void Matrix3::scale2D(Vector2D scale)
	{
		*this *= Matrix3(scale.x, 0.0f, 0.0f,
			0.0f, scale.y, 0.0f,
			0.0f, 0.0f, 1.0f);
	}

	Matrix3 Matrix3::operator*(const Matrix3 & other) const
	{
		Matrix3 result;
		for (unsigned int row = 0; row < 3; row++) {
			for (unsigned int col = 0; col < 3; col++) {
				float sum = 0.0f;
				for (unsigned int i = 0; i < 3; i++)
					sum += getValue(row, i) * other.getValue(i, col);
				result.setValue(row, col, sum);
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
		float x = this->getValue(0, 0) * vec.x + this->getValue(0, 1) * vec.y + this->getValue(0, 2);
		float y = this->getValue(1, 0) * vec.x + this->getValue(1, 1) * vec.y + this->getValue(1, 2);
		return Vector2D(x, y);
	}

	Rect Matrix3::operator*(const Rect & rect) const
	{
		return Rect(*this * rect.leftBottom, *this * rect.rightTop);
	}
}
