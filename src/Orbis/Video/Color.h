#pragma once

namespace Video
{
	struct Color
	{
	public:
		// white color
		static const Color White;

		// green color
		static const Color Green;

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
