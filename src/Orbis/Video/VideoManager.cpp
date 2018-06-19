#include "VideoManager.h"

#include <iostream>

namespace Video
{
	VideoManager* VideoManager::getInstance()
	{
		static VideoManager instance;
		return &instance;
	}

	void VideoManager::clear()
	{
		VideoManager::getInstance()->getRenderDevice()->clear();

		for (std::map<std::string, Texture*>::iterator it = m_textures.begin(); it != m_textures.end(); it++)
			delete (*it).second;
		m_textures.clear();

		for (std::map<ShaderPaths, Shader*>::iterator it = m_shaders.begin(); it != m_shaders.end(); it++)
			delete (*it).second;
		m_shaders.clear();

		m_textureAtlas.clear();
	}

	void VideoManager::start()
	{
		getTextureAtlas()->generate();
	}

	void VideoManager::render()
	{
		getRenderDevice()->render();
	}

	Texture* VideoManager::getTexture(std::string assetPath, bool flipVertically)
	{
		if (m_textures[assetPath])
			return m_textures[assetPath];

		Texture* texture = new Texture(assetPath, flipVertically);
		m_textures[assetPath] = texture;
		return texture;
	}

	Shader* VideoManager::getShader(std::string vertexShaderAssetPath, std::string fragmentShaderAssetPath)
	{
		ShaderPaths shaderPaths = ShaderPaths(vertexShaderAssetPath, fragmentShaderAssetPath);
		if (m_shaders[shaderPaths])
			return m_shaders[shaderPaths];

		Shader* shader = new Shader(vertexShaderAssetPath, fragmentShaderAssetPath);
		m_shaders[shaderPaths] = shader;
		return shader;
	}
}