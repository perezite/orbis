#include "Renderer.h"

namespace Components
{
	Renderer::Renderer()
		: m_shader(NULL), m_texture(NULL), m_mesh(NULL)
	{}

	bool Renderer::IsBatchEqualTo(Renderer* const other) const
	{
		bool areTexturesBothNull = m_texture == NULL && other->m_texture == NULL;
		bool areTexturesEqual = m_texture == other->m_texture;
		bool areTexturesBatchEqual = areTexturesBothNull || areTexturesEqual;

		bool areShadersBatchEqual = m_shader == other->m_shader;

		return areTexturesBatchEqual && areShadersBatchEqual;
	}
}
