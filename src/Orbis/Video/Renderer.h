#pragma once

#include "RenderMode.h"
#include "Shader.h"

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
	class Renderer
	{
	public:
		// dtor
		virtual ~Renderer();

		// begin primitive
		void BeginPrimitive(RenderMode renderMode);

		// end primitive
		void EndPrimitive(float rotation);

		// set vertex 2d
		void SetVertex2D(Vector2D position);

	private:
		// the vertices of the primitive
		std::vector<Vector2D> m_vertices;

		// the shader
		Shader m_shader;

		// the current render mode
		RenderMode m_renderMode;
	};
}