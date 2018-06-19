#pragma once

#include "Window.h"
#include "RenderDevice.h"
#include "Texture.h"
#include "Shader.h"
#include "TextureAtlas.h"

#include <string>
#include <map>

typedef std::tuple<std::string, std::string> ShaderPaths;

namespace Video
{
	class VideoManager
	{
	public:
		// get instance
		static VideoManager* getInstance();

		// clear the manager
		void clear();

		// start the manager
		void start();

		// render
		void render();

		// get the texture atlas
		TextureAtlas* getTextureAtlas() { return &m_textureAtlas; }

		// get or load a texture
		Texture* getTexture(std::string assetPath, bool flipVertically = true);

		// get or load a shader
		Shader* getShader(std::string vertexShaderAssetPath, std::string fragmentShaderAssetPath);

		// get the winow
		Window* getWindow() { return &m_window; }

		// get the render device
		RenderDevice* getRenderDevice() { return &m_renderDevice; }

	protected:
		// singleton constructor
		VideoManager() { };

	private:
		// the textures
		std::map<std::string, Texture*> m_textures;

		// the shaders
		std::map<ShaderPaths, Shader*> m_shaders;

		// the texture atlas
		TextureAtlas m_textureAtlas;

		// the window
		Window m_window;

		// the render device
		RenderDevice m_renderDevice;
	};
}
