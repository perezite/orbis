#include "Matrix4.h"

#include <math.h>

namespace Math
{
	Matrix4::Matrix4()
	{
		m_values[0] = 1.0f; m_values[1] = 0.0f; m_values[2] = 0.0f; m_values[3] = 0.0f;
		m_values[4] = 0.0f; m_values[5] = 1.0f; m_values[6] = 0.0f; m_values[7] = 0.0f;
		m_values[8] = 0.0f; m_values[9] = 0.0f; m_values[10] = 1.0f; m_values[11] = 0.0f;
		m_values[12] = 0.0f; m_values[13] = 0.0f; m_values[14] = 0.0f; m_values[15] = 1.0f;
	}

	Matrix4 Matrix4::From2DTransform(const Matrix3 & trans2D)
	{
		Matrix4 mat;
		mat.SetValue(0, 0, trans2D.GetValue(0, 0)); mat.SetValue(0, 1, trans2D.GetValue(0, 1)); mat.SetValue(0, 2, 0.0f); mat.SetValue(0, 3, trans2D.GetValue(0, 2));
		mat.SetValue(1, 0, trans2D.GetValue(1, 0)); mat.SetValue(1, 1, trans2D.GetValue(1, 1)); mat.SetValue(1, 2, 0.0f); mat.SetValue(1, 3,trans2D.GetValue(1, 2));

		return mat;
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

}
