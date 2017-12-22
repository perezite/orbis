#pragma once

#include "Texture.h"
#include "Shader.h"
#include "Color.h"

namespace Video
{
	class Material
	{
	public:
		// ctor
		Material() : m_texture(NULL), m_shader(NULL), m_isColorUsed(false) {}

		// set texture
		void SetTexture(Texture* const texture) { m_texture = texture; }

		// get texture 
		Texture* GetTexture() const { return m_texture; }

		// set shader
		void SetShader(Shader* const shader) { m_shader = shader; }

		// get shader 
		Shader* GetShader() const { return m_shader; }

		// set color
		void SetColor(const Color& color) { m_color = color; }

		// get color
		const Color& GetColor() const { return m_color; }

		// set is color used
		void SetIsColorUsed(bool isColorUsed) { m_isColorUsed = isColorUsed; }

		// get is color used
		bool GetIsColorUsed() const { return m_isColorUsed; }

		// equality 
		bool operator==(const Material& other) const {
			return m_texture == other.GetTexture() && m_shader == other.GetShader() && m_color == other.GetColor() && m_isColorUsed == other.GetIsColorUsed();
		}

	private:
		// the texture
		Texture* m_texture;

		// the shader
		Shader* m_shader;

		// the color
		Color m_color;

		// is the color used
		bool m_isColorUsed;
	};
}