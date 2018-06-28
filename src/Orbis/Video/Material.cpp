#include "Material.h"

#include "../../Base/Math/MathHelper.h"
using namespace base::math;

namespace orb
{
	namespace video
	{
		bool Material::isBatchEqualTo(Material * const other) const
		{
			bool texturesBatchEqual = areTexturesBatchEqual(this->getTexture(), other->getTexture());

			bool shadersBatchEqual = m_shader == other->m_shader;

			float eps = 0.001f;
			bool colorsBatchEqual =
				MathHelper::approx(m_color.r, other->m_color.r, eps)
				&& MathHelper::approx(m_color.g, other->m_color.g, eps)
				&& MathHelper::approx(m_color.b, other->m_color.b, eps)
				&& MathHelper::approx(m_color.a, other->m_color.a, eps);

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
			if (thisTex->isUsingAtlassing() && !otherTex->isUsingAtlassing())
				return false;
			if (!thisTex->isUsingAtlassing() && otherTex->isUsingAtlassing())
				return false;

			// compare direct textures
			if (!thisTex->isUsingAtlassing() && !otherTex->isUsingAtlassing())
				return thisTex == otherTex;

			// compare atlas charts
			if (thisTex->isUsingAtlassing() && otherTex->isUsingAtlassing())
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
}