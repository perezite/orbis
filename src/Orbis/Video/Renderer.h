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
		// ctor
		Renderer();

		// dtor
		virtual ~Renderer();

		// add geometry to the renderer
		void AddGeometry(std::vector<Vector2D> vertices, int indices[]);

		// render
		void Render(float rotation);

	private:
		// the vertices of the primitive
		std::vector<Vector2D> vertices;
	};
}