#pragma once

namespace Video
{
	class Color
	{
	public:
		// ctor
		Color(float red, float green, float blue, float alpha = 1.0f) :
			m_red(red), m_green(green), m_blue(blue), m_alpha(alpha)
		{ }

		// ctor
		Color() :
			m_red(0.0f), m_green(0.0f), m_blue(0.0f), m_alpha(1.0f)
		{ }

		// get red
		float GetRed() const { return m_red; }

		// get green
		float GetGreen() const { return m_green; }

		// get blue
		float GetBlue() const { return m_blue; }

		// get alpha
		float GetAlpha() const { return m_alpha; }

		// set red
		void SetRed(float red) { m_red = red; }

		// set green
		void SetGreen(float green) { m_green = green; }

		// set green
		void SetBlue(float blue) { m_blue = blue; }

		// set alpha
		void SetAlpha(float alpha) { m_alpha = alpha; }

		// equality
		bool operator==(const Color& other) const { 
			return m_red == other.GetRed() && m_green == other.GetGreen() && m_blue == other.GetBlue() && m_alpha == other.GetAlpha();
		}

	public:
		// white color
		static const Color White;

	private:
		// red
		float m_red;

		// green
		float m_green;

		// blue
		float m_blue;

		// alpha
		float m_alpha;
	};

}
