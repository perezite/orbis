#pragma once

namespace Math
{
	class Vector3D
	{
	public:
		Vector3D(float x, float y, float z) :
			m_x(x), m_y(y), m_z(z)
		{ }

		// get x coordinate
		float GetX() const { return m_x; }

		// get y coordinate
		float GetY() const { return m_y; }

		// get z coorindate
		float GetZ() const { return m_z; }

	private: 
		// x coordinate
		float m_x;
		
		// y coordinate
		float m_y;
		
		// z coorindate
		float m_z;
	};
}
