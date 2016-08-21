#include "Event.h"

#include "..\..\Base\System\Exception.h"
using namespace System;

namespace Input
{
	Event::Type Event::GetType()
	{
		switch (m_sdlEvent.type)
		{
		case SDL_QUIT:
			return Type::Quit;
		case SDL_KEYDOWN:
			return Type::KeyDown;
		case SDL_KEYUP:
			return Type::KeyUp;
		default:
			return Type::Unknown;
		}
	}

	KeyCode Event::GetKeyCode()
	{
		// check if operation is supported for this type of event
		static std::vector<Type> supportedTypes;
		supportedTypes.push_back(Type::KeyUp);
		supportedTypes.push_back(Type::KeyDown);
		AssertType(supportedTypes);

		return (KeyCode)m_sdlEvent.key.keysym.sym;
	}

	void Event::AssertType(std::vector<Type> types)
	{
		bool match = std::find(types.begin(), types.end(), GetType()) != types.end();
		if (match == false)
		{
			throw Exception("Operation is not supported for this type of SDLEvent");
		}
	}
}
