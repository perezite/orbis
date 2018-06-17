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
		static VideoManager* GetInstance();

		// clear the manager
		void Clear();

		// start the manager
		void Start();

		// render
		void Render();

		// get the texture atla
		TextureAtlas* GetTextureAtlas();

		// get or load a texture
		Texture* GetTexture(std::string assetPath, bool flipVertically = true);

		// get or load a shader
		Shader* GetShader(std::string vertexShaderAssetPath, std::string fragmentShaderAssetPath);

		// get the winow
		Window* GetWindow() { return &m_window; }

		// get the render device
		RenderDevice* GetRenderDevice() { return &m_renderDevice; }

	protected:
		// singleton constructor
		VideoManager();

	private:
		// the texture atlas
		TextureAtlas* m_textureAtlas;

		// the textures
		std::map<std::string, Texture*> m_textures;

		// the shaders
		std::map<ShaderPaths, Shader*> m_shaders;

		// the window
		Window m_window;

		// the render device
		RenderDevice m_renderDevice;
	};
}
