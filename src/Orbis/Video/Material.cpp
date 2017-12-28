#include "Material.h"

#include "../../Base/Math/MathHelper.h"
using namespace Math;

namespace Video
{
	bool Material::IsBatchEqualTo(Material * const other) const
	{
		bool areTexturesBothNull = m_texture == NULL && other->m_texture == NULL;
		bool areTexturesEqual = m_texture == other->m_texture;
		bool areTexturesBatchEqual = areTexturesBothNull || areTexturesEqual;

		bool areShadersBatchEqual = m_shader == other->m_shader;

		float eps = 0.001f;
		bool areBothColorsOff = m_hasColor == other->m_hasColor == false;
		bool areColorsApproxEqual = 
			MathHelper::Approx(m_color.r, other->m_color.r, eps)
			&& MathHelper::Approx(m_color.g, other->m_color.g, eps)
			&& MathHelper::Approx(m_color.b, other->m_color.b, eps)
			&& MathHelper::Approx(m_color.a, other->m_color.a, eps);
		bool areColorsBatchEqual = areBothColorsOff || areColorsApproxEqual;

		return areTexturesBatchEqual && areShadersBatchEqual && areColorsBatchEqual;
	}

	void Material::PrepareShaderVariables()
	{
		// note: vertex and tex coord data is set directly in the render device
		if (m_texture != NULL)
			m_shader->SetUniform("u_sSampler", 0);

		if (m_hasColor)
			m_shader->SetUniform("u_vColor", m_color);
			
	}
}
