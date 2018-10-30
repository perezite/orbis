#pragma once

#include "Window.h"
#include "RenderDevice.h"
#include "DebugRenderDevice.h"
#include "Texture.h"
#include "Shader.h"
#include "TextureAtlas.h"

#include <string>
#include <map>

typedef std::tuple<std::string, std::string> ShaderConfig;
typedef std::tuple<std::string, bool> TextureConfig;

namespace orb
{
	class VideoManager
	{
	public:
		// get instance
		static VideoManager* instance();

		// clear the manager
		void clear();

		// render
		void render();

		// get the texture atlas
		TextureAtlas* getTextureAtlas() { return &m_textureAtlas; }

		// get or load a texture
		Texture* getTexture(const std::string& assetPath, bool flipVertically = true);

		// get or load a shader
		Shader* getShader(const std::string& vertexShaderAssetPath, const std::string& fragmentShaderAssetPath);

		// get the winow
		Window* getWindow() { return &m_window; }

		// get the render device
		RenderDevice* getRenderDevice() { return &m_renderDevice; }

		// get the debug render device
		DebugRenderDevice* getDebugRenderDevice() { return &m_debugRenderDevice; }

	protected:
		// singleton constructor
		VideoManager() { };

	private:
		// the textures
		std::map<TextureConfig, Texture*> m_textures;

		// the shaders
		std::map<ShaderConfig, Shader*> m_shaders;

		// the texture atlas
		TextureAtlas m_textureAtlas;

		// the window
		Window m_window;

		// the render device
		RenderDevice m_renderDevice;

		// the debug render device
		DebugRenderDevice m_debugRenderDevice;
	};
}