#include "VideoManager.h"

#include "../Core/LogUtil.h"

#include "../../Base/Base.h"
using namespace base;

#include <sstream>
#include <iostream>

namespace orb
{
	VideoManager* VideoManager::instance()
	{
		static VideoManager instance;
		return &instance;
	}

	void VideoManager::clear()
	{
		VideoManager::instance()->getRenderDevice()->clear();

		for (std::map<TextureConfig, Texture*>::iterator it = m_textures.begin(); it != m_textures.end(); it++)
			delete (*it).second;
		m_textures.clear();

		for (std::map<ShaderConfig, Shader*>::iterator it = m_shaders.begin(); it != m_shaders.end(); it++)
			delete (*it).second;
		m_shaders.clear();

		m_textureAtlas.clear();
	}

	void VideoManager::render()
	{
		getRenderDevice()->render();
	}

	Texture* VideoManager::getTexture(const std::string& assetPath, bool flipVertically)
	{
		TextureConfig config = TextureConfig(assetPath, flipVertically);
		if (m_textures[config])
			return m_textures[config];

		Texture* texture = new Texture(assetPath, flipVertically);
		m_textures[config] = texture;
		return texture;
	}

	Shader* VideoManager::getShader(const std::string& vertexShaderAssetPath, const std::string& fragmentShaderAssetPath)
	{
		ShaderConfig config = ShaderConfig(vertexShaderAssetPath, fragmentShaderAssetPath);
		if (m_shaders[config])
			return m_shaders[config];

		Shader* shader = new Shader(vertexShaderAssetPath, fragmentShaderAssetPath);
		m_shaders[config] = shader;
		return shader;
	}
}