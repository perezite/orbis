#include "GUIHelper.h"

#include "SDL2/SDL.h"

namespace GUI
{
	void GUIHelper::ShowMessageBox(std::string message, std::string title)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(), message.c_str(), NULL);
	}
}
