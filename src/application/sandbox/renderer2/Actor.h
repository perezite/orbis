#pragma once

#include "Drawable.h"

namespace sb
{
	namespace renderer2
	{
		class Actor : public Drawable 
		{
		public:
			virtual void rotate(float dt) = 0;
		};
	}
}