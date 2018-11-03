#pragma once

namespace orb
{
	class Component
	{
	public:
		virtual ~Component() {};

		virtual void update() { };

		virtual void render() { };
	};
}
