#pragma once

#include "Color.h"
#include "RenderMode.h"

#include "../../Base/Math/Matrix4.h"
using namespace Math;

#ifdef __ANDROID__
#include <GLES2/gl2.h>	
#include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#endif

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
		void SetTransformUniform(Matrix4& mat);

		// set the sample uniform
		void SetSamplerUniform(int sampler);

		// enable the shader
		void Use();

		// disable the shader
		void Unuse();
	};
}
