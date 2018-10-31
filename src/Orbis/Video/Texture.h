#pragma once

#include "TextureAtlas.h"

#include "../Libraries/GL.h"
#include "../Libraries/SDL.h"
#include "../Game/Level.h"

#include "../../Base/Base.h"
using namespace base;

#include <string>
#include <set>

namespace orb
{
	class Level;

	class TextureChart;

	class Texture
	{
	public:
		// ctor
		Texture(const std::string& assetPath, bool flipVertically = true);

		// dtor
		virtual ~Texture();

		// get the asset path
		const std::string& getAssetPath() const { return m_assetPath; }

		// get the sdl surface
		SDL_Surface* getSurface() { return m_surface; }

		// get the handle
		GLuint getHandle() { return m_handle; }

		// is the texture charted
		bool isCharted() const { return m_parentChart != NULL; }

		// get the parent chart
		const TextureChart* getParentChart() const { return m_parentChart; }

		// set the atlas parentChart of the texture
		void setParentChart(TextureChart* parentChart) { m_parentChart = parentChart; }

		// transform given UV coordinates to actual charted coordinates
		Vector2f computeChartedUV(const Vector2f& texUV);

		// bind this texture
		void bind();

	protected:
		// flip the given surface. The pointer to the given surface is invalidated and gets replaced by the returned pointer 
		SDL_Surface* flipSurfaceVertically(SDL_Surface* surface);

	private:
		// the texture asset path
		std::string m_assetPath;

		// the texture id
		GLuint m_handle;

		// the image surface
		SDL_Surface* m_surface;

		// the parent chart containing the texture
		TextureChart* m_parentChart;
	};
}