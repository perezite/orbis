#include "Material.h"

#include "../../Base/Math/MathHelper.h"
using namespace Math;

namespace Video
{
	bool Material::IsBatchEqualTo(Material * const other) const
	{
		bool areTexturesBatchEqual = AreTexturesBatchEqual(this->GetTexture(), other->GetTexture());

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

	bool Material::AreTexturesBatchEqual(Texture* const thisTex, Texture* const otherTex) const
	{
		// compare empty textures
		if (thisTex == NULL && otherTex != NULL)
			return false;
		if (thisTex != NULL && otherTex == NULL)
			return false;
		if (thisTex == NULL && otherTex == NULL)
			return true;

		// compare atlassing
		if (thisTex->UseAtlassing() && !otherTex->UseAtlassing())
			return false;
		if (!thisTex->UseAtlassing() && otherTex->UseAtlassing())
			return false;

		// compare direct textures
		if (!thisTex->UseAtlassing() && !otherTex->UseAtlassing())
			return thisTex == otherTex;

		// compare atlas charts
		if (thisTex->UseAtlassing() && otherTex->UseAtlassing())
			return thisTex->GetAtlasChart() == otherTex->GetAtlasChart();

		throw Exception("Something went really wrong!");
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
