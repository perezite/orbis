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
			MathHelper::Approx(m_color.GetRed(), other->m_color.GetRed(), eps)
			&& MathHelper::Approx(m_color.GetGreen(), other->m_color.GetGreen(), eps)
			&& MathHelper::Approx(m_color.GetBlue(), other->m_color.GetBlue(), eps)
			&& MathHelper::Approx(m_color.GetAlpha(), other->m_color.GetAlpha(), eps);
		bool areColorsBatchEqual = areBothColorsOff || areColorsApproxEqual;

		return areTexturesBatchEqual && areShadersBatchEqual && areColorsBatchEqual;
	}
}
