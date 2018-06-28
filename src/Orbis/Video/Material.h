#pragma once

#include "Texture.h"
#include "Shader.h"
#include "Color.h"

namespace video
{
	class Material
	{
	public:
		// ctor
		Material() : m_texture(NULL), m_shader(NULL), m_color(Color::White) {}

		// set texture
		void setTexture(Texture* const texture) { m_texture = texture; }

		// get texture 
		Texture* getTexture() const { return m_texture; }

		// set shader
		void setShader(Shader* const shader) { m_shader = shader; }

		// get shader 
		Shader* getShader() const { return m_shader; }

		// set color
		void setColor(const Color& color) { m_color = color; }

		// get color
		Color& getColor() { return m_color; }

		// can the materials be batched
		bool isBatchEqualTo(Material* const other) const;

		// set the variables of the shader according to the shader properties
		void prepareShaderVariables();

	protected:
		// can the textures be batched
		bool areTexturesBatchEqual(Texture* const thisTex, Texture* const otherTex) const;

	private:
		// the texture
		Texture* m_texture;

		// the shader
		Shader* m_shader;

		// the color
		Color m_color;
	};
}