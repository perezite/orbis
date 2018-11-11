#include "Triangle1.h"

#include <iostream>

namespace sb 
{
	namespace triangle1 
	{
		GLuint Triangle1::m_shader;

		std::map<std::string, GLuint> Triangle1::m_attributeLocations;

		void Triangle1::run()
		{
			Triangle1Util::initSDL();
			init();

			bool running = true;
			while (running) {
				running = Triangle1Util::updateInput();
				render();
				Triangle1::flip();
			}

			Triangle1Util::close();
		}

		void Triangle1::init()
		{
			m_shader = Triangle1Util::createShader(Triangle1Util::getDiffuseVertexShaderCode(), Triangle1Util::getDiffuseFragmentShaderCode());
			m_attributeLocations["a_vPosition"] = glGetAttribLocation(m_shader, "a_vPosition");
			m_attributeLocations["a_vColor"] = glGetAttribLocation(m_shader, "a_vColor");
		}

		void Triangle1::render()
		{
			std::vector<Vertex> vertices; computeVertices(vertices);
			std::vector<GLushort> indices; computeIndices(indices);
			prepareRendering(vertices);

			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, &(indices[0]));

			finalize();
		}

		void Triangle1::flip()
		{
			Triangle1Util::flip();
		}

		void Triangle1::computeVertices(std::vector<Vertex>& result)
		{
			result = { Vertex(-0.5f, -0.5f, 1, 0, 0, 1),
						Vertex(0.5f, -0.5f, 0, 1, 0, 1),
						Vertex(0.0f,  0.5f, 0, 0, 1, 1) };
		}

		void Triangle1::computeIndices(std::vector<GLushort>& result)
		{
			result = { 0, 1, 2 };
		}

		void Triangle1::prepareRendering(std::vector<Vertex>& vertices)
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			Triangle1Util::activateShader(m_shader);

			Triangle1Util::attachVertexArrayToShaderAttribute(m_attributeLocations["a_vPosition"], 2, GL_FLOAT, sizeof(Vertex), &(vertices[0].x));
			Triangle1Util::attachVertexArrayToShaderAttribute(m_attributeLocations["a_vColor"], 4, GL_UNSIGNED_BYTE, sizeof(Vertex), &(vertices[0].r));
		}

		void Triangle1::finalize()
		{
			Triangle1Util::detachVertexArrayFromShaderAttribute(m_attributeLocations["a_vColor"]);
			Triangle1Util::detachVertexArrayFromShaderAttribute(m_attributeLocations["a_vPosition"]);

			glDisable(GL_BLEND);
			Triangle1Util::activateShader(0);

			GLenum error = glGetError();
			if (glGetError() != GL_NO_ERROR)
				std::cout << "GL error: " << error << std::endl;
		}

	}
}
