#pragma once

#include "Triangle1SandboxUtil.h"

#include <string>
#include <map>
#include <vector>


namespace app
{
	class Vertex
	{
	public:
		Vertex(float x_, float y_, unsigned char r_, unsigned char  g_, unsigned char  b_, unsigned char  a_)
			: x(x_), y(y_), r(r_), g(g_), b(b_), a(a_)
		{

		}

		float x, y;
		unsigned char r, g, b, a;
	};

	class RotatingTriangleSandbox
	{
	public:
		static void run();

	protected:
		static void init();

		static void render();

		static void flip();
		
		static void computeVertices(std::vector<Vertex>& result);

		static void computeIndices(std::vector<GLushort>& result);

		static void prepareRendering(std::vector<Vertex>& rendering);

		static void finalize();

	private:
		static GLuint m_shader;

		static std::map<std::string, GLuint> m_attributeLocations;
	};
}