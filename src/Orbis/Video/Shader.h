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
		// ctor
		Shader(std::string vertexAssetPath, std::string fragmentAssetPath);

		// dtor
		~Shader();

		// get the position attribute location
		int GetPositionAttributeHandle();

		// get the tex coord attribute handle
		int GetTexCoordAttributeHandle();

		// set the transform uniform
		void SetModelViewMatrix(const Matrix3& mat);

		// set the sample uniform
		void SetSamplerUniform(int sampler);

		// enable the shader
		void Use();

		// disable the shader
		void Unuse();
	};
}
