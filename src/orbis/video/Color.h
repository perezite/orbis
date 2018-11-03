#pragma once

namespace orb
{
	// a color is defined as a mix of red, green and blue values
	class Color
	{
	public:
		static const Color White;

	public:
		Color(unsigned char r_ = 0, unsigned char g_ = 0, unsigned char b_ = 0) 
			: r(r_), g(g_), b(b_)
		{};

		virtual ~Color() 
		{};


	public:
		unsigned char r;

		unsigned char g;

		unsigned char b;
	};
}
