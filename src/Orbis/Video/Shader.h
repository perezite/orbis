#pragma once

#include "Color.h"
#include "RenderMode.h"

#include "../../Base/Math/Vector2D.h"
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
		Shader();

		// dtor
		~Shader();

		// set the vertex colors
		void SetVertexColors(std::vector<Color> colors) { m_vertexColors = colors; }

		// set the vertex positions
		void SetVertices(std::vector<Vector2D> positions) { m_vertexPositions = positions; }

		// draw the shader
		void Draw(RenderMode renderMode);

	protected:
		// load a shader
		GLuint LoadShader(std::string shaderCode, GLenum type);

		// link the shader program
		void Link();

		// convert to vertex buffer
		GLfloat* GetVertexBuffer(std::vector<Vector2D> vertices, std::vector<Color> colors);
	private:
		// the vertex shader code
		static const std::string VertexShaderCode;

		// the fragment shader code
		static const std::string FragmentShaderCode;

		// the compiled vertex shader
		GLuint m_vertexShader;

		// the compiled fragment shader
		GLuint m_fragmentShader;

		// the shader program
		GLuint m_shaderProgram;

		// the vertex positions
		std::vector<Vector2D> m_vertexPositions;

		// the vertex colors
		std::vector<Color> m_vertexColors;

		// position parameter index
		static const int PositionShaderAttributeLocation = 0;

		// color parameter index
		static const int ColorShaderAttributeLocation = 1;
	};
}