#pragma once

#include "../video/Transformable.h"
#include "../video/Drawable.h"

namespace orb
{
	class Component : public Transformable, public Drawable
	{
	public:
		virtual void render() { };
	};
}
