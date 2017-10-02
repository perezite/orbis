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

		// set vertices
		void SetVertices(std::vector<Vector2D> positions, std::vector<Color> colors);

		// set indices
		void SetIndices(std::vector<unsigned int> indices);

		// render
		void Render(std::vector<Vector2D> positions, std::vector<Color> colors, float rotation, RenderMode renderMode);

	protected:
		// compile the shader
		GLuint Compile(std::string shaderCode, GLenum type);

		// link the shader
		void Link();

		// get vertex array
		GLfloat* GetVertexArray(std::vector<Vector2D> vertices, std::vector<Color> colors);
	private:
		// number of elements per color
		static const int32_t ColorNumElements;

		// number of elements per position
		static const int32_t PositionNumElements;

		// size of one position
		static const int32_t PositionSize;

		// size of one vertex
		static const int32_t VertexSize;

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

		// the vertex buffer
		GLuint m_vertexBuffer;

		// the index buffer
		GLuint m_indexBuffer;

		// the vertex array
		GLfloat* m_vertexArray;

		// numer of elements to draw
		GLuint m_numVertices;

		// position parameter index
		int m_positionAttributeLocation;

		// color parameter index
		int m_colorAttributeLocation;

		// rotation parameter index
		int m_rotationAttributeLocation;
	};
}