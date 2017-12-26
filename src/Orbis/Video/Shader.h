#pragma once

#include "Color.h"
#include "RenderMode.h"

#include "../../Base/Math/Matrix4.h"
using namespace Math;

#include <string>
#include <vector>

namespace Video
{
	class Shader
	{
	public:
		// get static diffuse shader
		static Shader* GetDiffuseShader();

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

		// set a uniform value
		void SetUniform(std::string id, const Matrix4& mat);

		// enable the shader
		void Use();

		// disable the shader
		void Unuse();

	private: 
		// the shader program id
		GLuint m_programId = -1;
	};
}
