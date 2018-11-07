#pragma once

#include "Helper.h"

#include <string>
#include <map>
#include <vector>


namespace app
{
	class RotatingTriangleSandbox
	{
	public:
		static void run();

	protected:
		static void init();

		static void render();

		static void flip();
		
		static void computeVertices(std::vector<GLfloat>& result);

		static void computeIndices(std::vector<GLushort>& result);

		static void prepareRendering(std::vector<GLfloat>& rendering);

		static void cleanupRendering();

	private:
		static GLuint m_shader;

		static std::map<std::string, GLuint> m_attributeLocations;
	};
}