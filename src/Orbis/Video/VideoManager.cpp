#include "VideoManager.h"

#include <iostream>

namespace Video
{
	VideoManager* VideoManager::GetInstance()
	{
		static VideoManager instance;
		return &instance;
	}

	VideoManager::VideoManager() :
		m_textureAtlas(NULL)
	{ 
	}

	void VideoManager::Clear()
	{
		VideoManager::GetInstance()->GetRenderDevice()->ClearRenderables();

		for (std::map<std::string, Texture*>::iterator it = m_textures.begin(); it != m_textures.end(); it++)
			delete (*it).second;
		m_textures.clear();

		for (std::map<std::tuple<std::string, std::string>, Shader*>::iterator it = m_shaders.begin(); it != m_shaders.end(); it++)
			delete (*it).second;
		m_shaders.clear();

		delete m_textureAtlas;
		m_textureAtlas = NULL;
	}

	void VideoManager::Start()
	{
		GetTextureAtlas()->Generate();
	}

	void VideoManager::Render()
	{
		GetRenderDevice()->Render();
	}

	TextureAtlas* VideoManager::GetTextureAtlas()
	{
		if (!m_textureAtlas)
			m_textureAtlas = new TextureAtlas();
		
		return m_textureAtlas;
	}

	Texture* VideoManager::GetTexture(std::string assetPath, bool flipVertically)
	{
		if (m_textures[assetPath])
			return m_textures[assetPath];

		Texture* texture = new Texture(assetPath, flipVertically);
		m_textures[assetPath] = texture;
		return texture;
	}

	Shader* VideoManager::GetShader(std::string vertexShaderAssetPath, std::string fragmentShaderAssetPath)
	{
		ShaderPaths shaderPaths = ShaderPaths(vertexShaderAssetPath, fragmentShaderAssetPath);
		if (m_shaders[shaderPaths])
			return m_shaders[shaderPaths];

		Shader* shader = new Shader(vertexShaderAssetPath, fragmentShaderAssetPath);
		m_shaders[shaderPaths] = shader;
		return shader;
	}
}