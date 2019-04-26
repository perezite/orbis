#pragma once

#include "Color.h"
#include "RenderMode.h"

#include <string>
#include <vector>

namespace orb
{
	class Shader
	{
	public:
		// ctor
		Shader(std::string vertexShaderAssetPath, std::string fragmentShaderAssetPath);

		// dtor
		~Shader();

		// get an attribute handle
		int getAttributeLocation(std::string id);

		// set a uniform value
		void setUniform(std::string id, int value);

		// set a uniform value
		void setUniform(std::string id, const Color& color);

		// enable the shader
		void use();

		// disable the shader
		void unuse();

	private:
		// the shader program id
		GLuint m_programId = -1;
	};
}