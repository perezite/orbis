#pragma once

#include "Color.h"
#include "RenderMode.h"

#include <string>
#include <vector>

namespace Video
{
	class Shader
	{
	public:
		// get static diffuse shader
		static Shader* GetDiffuseShader();

		// get static flat particle shader
		static Shader* GetDiffuseParticleShader();

		// get static flat shader
		static Shader* GetFlatShader();

	public:
		// ctor
		Shader(std::string vertexAssetPath, std::string fragmentAssetPath);

		// dtor
		~Shader();

		// get an attribute handle
		int GetAttributeLocation(std::string id);

		// set a uniform value
		void SetUniform(std::string id, int value);

		// set a uniform value
		void SetUniform(std::string id, const Color& color);

		// enable the shader
		void Use();

		// disable the shader
		void Unuse();

	private: 
		// the shader program id
		GLuint m_programId = -1;
	};
}
