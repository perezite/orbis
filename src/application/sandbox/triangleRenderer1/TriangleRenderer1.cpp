#include "TriangleRenderer1.h"

#include <iostream>

namespace sb 
{
	namespace triangleRenderer1 
	{
		GLuint TriangleRenderer1::m_shader;

		std::map<std::string, GLuint> TriangleRenderer1::m_attributeLocations;

		void TriangleRenderer1::run()
		{
			RenderUtil::initSDL();
			init();

			bool running = true;
			while (running) {
				running = RenderUtil::updateInput();
				render();
				TriangleRenderer1::flip();
			}

			RenderUtil::close();
		}

		void TriangleRenderer1::init()
		{
			m_shader = RenderUtil::createShader(RenderUtil::getDiffuseVertexShaderCode(), RenderUtil::getDiffuseFragmentShaderCode());
			m_attributeLocations["a_vPosition"] = glGetAttribLocation(m_shader, "a_vPosition");
			m_attributeLocations["a_vColor"] = glGetAttribLocation(m_shader, "a_vColor");
		}

		void TriangleRenderer1::render()
		{
			std::vector<Vertex> vertices; computeVertices(vertices);
			std::vector<GLushort> indices; computeIndices(indices);
			prepareRendering(vertices);

			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, &(indices[0]));

			finalize();
		}

		void TriangleRenderer1::flip()
		{
			RenderUtil::flip();
		}

		void TriangleRenderer1::computeVertices(std::vector<Vertex>& result)
		{
			result = { Vertex(-0.5f, -0.5f, 1, 0, 0, 1),
						Vertex(0.5f, -0.5f, 0, 1, 0, 1),
						Vertex(0.0f,  0.5f, 0, 0, 1, 1) };
		}

		void TriangleRenderer1::computeIndices(std::vector<GLushort>& result)
		{
			result = { 0, 1, 2 };
		}

		void TriangleRenderer1::prepareRendering(std::vector<Vertex>& vertices)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			RenderUtil::activateShader(m_shader);

			RenderUtil::attachVertexArrayToShaderAttribute(m_attributeLocations["a_vPosition"], 2, GL_FLOAT, sizeof(Vertex), &(vertices[0].x));
			RenderUtil::attachVertexArrayToShaderAttribute(m_attributeLocations["a_vColor"], 4, GL_UNSIGNED_BYTE, sizeof(Vertex), &(vertices[0].r));
		}

		void TriangleRenderer1::finalize()
		{
			RenderUtil::detachVertexArrayFromShaderAttribute(m_attributeLocations["a_vColor"]);
			RenderUtil::detachVertexArrayFromShaderAttribute(m_attributeLocations["a_vPosition"]);

			glDisable(GL_BLEND);
			RenderUtil::activateShader(0);

			GLenum error = glGetError();
			if (glGetError() != GL_NO_ERROR)
				std::cout << "GL error: " << error << std::endl;
		}

	}
}
