#pragma once

#include "../../Base/Math/Vector3D.h"
using namespace Math;

#include "Color.h"

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
		Shader();

		// dtor
		~Shader();

		// set the vertex colors
		void SetVertexColors(std::vector<Color> colors) { m_vertexColors = colors; }

		// set the vertex positions
		void SetVertexPositions(std::vector<Vector3D> positions) { m_vertexPositions = positions; }

	protected:
		// set the fragment shader source code
		virtual void SetFragmentShaderCode(std::string code);

		// load a shader
		GLuint LoadShader(std::string shaderCode, GLenum type);

	private:
		// the vertex shader code
		static const std::string m_vertexShaderCode;

		// the fragment shader code
		std::string m_fragmentShaderCode;

		// the compiled vertex shader
		GLuint m_vertexShader;

		// the compiled fragment shader
		GLuint m_fragmentShader;

		// the shader program
		GLuint m_shaderProgram;

		// the vertex colors
		std::vector<Color> m_vertexColors;

		// the vertex positions
		std::vector<Vector3D> m_vertexPositions;
	};
}