#pragma once

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#ifdef __ANDROID__
	#include <GLES2/gl2.h>	
	#include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
	#include <gl/glew.h>
	#include <SDL2/SDL_opengl.h>
	#include <gl/glu.h>
#endif

#include <vector>

namespace Video
{
	enum RenderMode
	{
		Triangle = GL_TRIANGLES
	};

	class Renderer
	{
	public:
		// initialize
		void Initialize();

		// dtor
		virtual ~Renderer();

		// begin primitive
		void BeginPrimitive(RenderMode renderMode);

		// end primitive
		void EndPrimitive();

		// set vertex 2d
		void SetVertex2D(Vector2D position);

		// set the window resolution (temporary, should be in GraphicsManager)
		void SetWindowResolution(Vector2D resolution);

	protected:	
		// load a shader from a program string
		GLuint LoadShader(const char *shaderSrc, GLenum type);

	private:
		// the vertices of the primitive
		std::vector<Vector2D> m_vertices;

		// the current render mode
		RenderMode m_renderMode;

		// the shader program
		int m_shaderProgram;

		// the vertex shader
		GLuint m_vertexShader;

		// the fragment shader
		GLuint m_fragmentShader;

		// the window resolution (only temporary, should be in GraphicsManager)
		Vector2D m_windowResolution;

		// position parameter index
		static const int PositionShaderAttributeLocation = 0;

		// color parameter index
		static const int ColorShaderAttributeLocation = 1;
	};
}