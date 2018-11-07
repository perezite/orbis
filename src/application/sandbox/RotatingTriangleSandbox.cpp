#include "RotatingTriangleSandbox.h"
// #include "Helper.h"

#include <iostream>

namespace app
{
	GLuint RotatingTriangleSandbox::m_shader;

	std::map<std::string, GLuint> RotatingTriangleSandbox::m_attributeLocations;

	void RotatingTriangleSandbox::run()
	{
		Helper::initSDL();
		init();

		bool running = true;
		while (running) {
			running = Helper::updateInput();
			render();
			Helper::flip();
		}

		Helper::cleanup();
	}

	void RotatingTriangleSandbox::init()
	{
		m_shader = Helper::createShader(Helper::getDiffuseVertexShaderCode(), Helper::getDiffuseFragmentShaderCode());
		m_attributeLocations["a_vPosition"] = glGetAttribLocation(m_shader, "a_vPosition");
		m_attributeLocations["a_vColor"] = glGetAttribLocation(m_shader, "a_vColor");
	}

	void RotatingTriangleSandbox::render()
	{
		std::vector<Vertex> vertices; computeVertices(vertices);
		std::vector<GLushort> indices; computeIndices(indices);
		prepareRendering(vertices);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, &(indices[0]));

		cleanupRendering();
	}

	void RotatingTriangleSandbox::flip()
	{
		Helper::flip();
	}

	void RotatingTriangleSandbox::computeVertices(std::vector<Vertex>& result)
	{
		result = {	Vertex(-0.5f, -0.5f, 1, 0, 0, 1),
					Vertex(0.5f, -0.5f, 0, 1, 0, 1),
					Vertex(0.0f,  0.5f, 0, 0, 1, 1) };
	}

	void RotatingTriangleSandbox::computeIndices(std::vector<GLushort>& result)
	{
		result = { 0, 1, 2 };
	}

	void RotatingTriangleSandbox::prepareRendering(std::vector<Vertex>& vertices)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		Helper::activateShader(m_shader);

		Helper::attachVertexArrayToShaderAttribute(m_attributeLocations["a_vPosition"], 2, GL_FLOAT, sizeof(Vertex), &(vertices[0].x));
		Helper::attachVertexArrayToShaderAttribute(m_attributeLocations["a_vColor"], 4, GL_UNSIGNED_BYTE, sizeof(Vertex), &(vertices[0].r));
	}

	void RotatingTriangleSandbox::cleanupRendering()
	{
		Helper::detachVertexArrayFromShaderAttribute(m_attributeLocations["a_vColor"]);
		Helper::detachVertexArrayFromShaderAttribute(m_attributeLocations["a_vPosition"]);

		glDisable(GL_BLEND);
		Helper::activateShader(0);
	}
}
