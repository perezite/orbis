#pragma once

#include <string>
#include <SDL_opengl.h>
#include <SDL.h>

namespace Video
{
	class Texture
	{
	public:
		// constructor
		Texture(std::string filePath);
		
		// destructor
		virtual ~Texture();

		// set the texture active
		void SetActive();

	private:
		// path to texture file
		std::string m_filePath;

		// the SDL surface containing the image
		SDL_Surface* m_surface;

		// the texture id
		GLuint m_textureId;

		// the highest texture ID used
		static GLuint m_highestTextureId;
	};
}