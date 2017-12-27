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
		Material() : m_texture(NULL), m_shader(NULL), m_hasColor(false) {}

		// set texture
		void SetTexture(Texture* const texture) { m_texture = texture; }

		// get texture 
		Texture* GetTexture() const { return m_texture; }

		// set shader
		void SetShader(Shader* const shader) { m_shader = shader; }

		// get shader 
		Shader* GetShader() const { return m_shader; }

		// set color
		void SetColor(const Color& color) { m_hasColor = true; m_color = color; }

		// get color
		Color& GetColor() { return m_color; }

		// set is color used
		void HasColor(bool isColorUsed) { m_hasColor = isColorUsed; }

		// get is color used
		bool HasColor() const { return m_hasColor; }

		// can the materials be batched
		bool IsBatchEqualTo(Material* const other) const;

		// set the variables of the shader according to the shader properties
		void PrepareShaderVariables();

	private:
		// the texture
		Texture* m_texture;

		// the shader
		Shader* m_shader;

		// the color
		Color m_color;

		// is the color used
		bool m_hasColor;
	};
}