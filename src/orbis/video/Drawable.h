#pragma once
#include "Window.h"
#include "Transform.h"

namespace orb
{
	class Drawable
	{
	public:
		virtual void draw(orb::Window& window, const orb::Transform& transform) = 0;
	};

}
