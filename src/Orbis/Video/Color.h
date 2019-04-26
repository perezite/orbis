#pragma once

namespace orb
{
	struct Color
	{
	public:
		// get the size of the color
		static unsigned int getCount() { return 4; }

	public:
		// black color
		static const Color Black;

		// white color
		static const Color White;

		// red color
		static const Color Red;

		// green color
		static const Color Green;

		// blue color
		static const Color Blue;

	public:
		// ctor
		Color(float r_, float g_, float b_, float a_ = 1.0f) :
			r(r_), g(g_), b(b_), a(a_)
		{ }

		// ctor
		Color() :
			r(0.0f), g(0.0f), b(0.0f), a(1.0f)
		{ }

	public:
		// red
		float r;

		// green
		float g;

		// blue
		float b;

		// alpha
		float a;
	};
}