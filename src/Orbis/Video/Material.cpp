#include "Material.h"

#include "../../Base/Base.h"
using namespace base;

namespace orb
{
	bool Material::isBatchEqualTo(Material * const other) const
	{
		bool texturesBatchEqual = areTexturesBatchEqual(this->getTexture(), other->getTexture());

		bool shadersBatchEqual = m_shader == other->m_shader;

		float eps = 0.001f;
		bool colorsBatchEqual =
			MathUtil::approx(m_color.r, other->m_color.r, eps)
			&& MathUtil::approx(m_color.g, other->m_color.g, eps)
			&& MathUtil::approx(m_color.b, other->m_color.b, eps)
			&& MathUtil::approx(m_color.a, other->m_color.a, eps);

		return texturesBatchEqual && shadersBatchEqual && colorsBatchEqual;
	}

	bool Material::areTexturesBatchEqual(Texture* const thisTex, Texture* const otherTex) const
	{
		// compare empty textures
		if (thisTex == NULL && otherTex != NULL)
			return false;
		if (thisTex != NULL && otherTex == NULL)
			return false;
		if (thisTex == NULL && otherTex == NULL)
			return true;

		// compare atlassing
		if (thisTex->isAtlassed() && !otherTex->isAtlassed())
			return false;
		if (!thisTex->isAtlassed() && otherTex->isAtlassed())
			return false;

		// compare direct textures
		if (!thisTex->isAtlassed() && !otherTex->isAtlassed())
			return thisTex == otherTex;

		// compare atlas charts
		if (thisTex->isAtlassed() && otherTex->isAtlassed())
			return thisTex->getAtlasChart() == otherTex->getAtlasChart();

		throw Exception("Something went really wrong!");
	}

	void Material::prepareShaderVariables()
	{
		// note: vertex and tex coord data is set directly in the render device
		if (m_texture != NULL)
			m_shader->setUniform("u_sSampler", 0);

		m_shader->setUniform("u_vColor", m_color);
	}
}