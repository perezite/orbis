#pragma once

namespace Video
{
	// represents an rgba color
	class Color
	{
	public:
		// default constructor
		Color() : m_red(0.0f), m_green(0.0f), m_blue(0.0f), m_alpha(1.0f) { }

		// constructor
		Color(float red, float green, float blue, float alpha) : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) { }

		// destructor
		virtual ~Color() { }

		// get red
		float GetRed() { return m_red; }

		// get green
		float GetGreen() { return m_green; }

		// get blue
		float GetBlue() { return m_blue; }

		// get alpha
		float GetAlpha() { return m_alpha; }

		// set red
		void SetRed(float red) { m_red = red; }

		// set green
		void SetGreen(float green) { m_green = green; }

		// set blue
		void SetBlue(float blue) { m_blue = blue; }

		// set alpha
		void SetAlpha(float alpha) { m_alpha = alpha; }

	public:
		static const Color Black;

	private:
		float m_red;
		float m_green;
		float m_blue;
		float m_alpha;
	};
}