#include "TriangleRenderer2.h"
#include <iostream>
#include <stddef.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <chrono>

namespace sb 
{
	namespace triangleRenderer2 
	{
		const unsigned int TriangleRenderer2::NumTrianglesHorz = 100;
		const unsigned int TriangleRenderer2::NumTrianglesVert = 100;
		
		Window TriangleRenderer2::m_window;
		Shader TriangleRenderer2::m_shader;
		Stopwatch TriangleRenderer2::m_stopwatch;
		std::vector<Triangle> TriangleRenderer2::m_triangles;
		VertexBuffer TriangleRenderer2::m_vertexBuffer;
		std::vector<Vertex> TriangleRenderer2::m_transformedVertices;

		void TriangleRenderer2::run()
		{
			m_window.init(1800, 1000);
			initGL();
			initTriangles();

			while (!m_window.hasQuitEvent()) {			
				m_window.update();
				update();
				render();
				display();
				m_window.flip();
			}

			close();
		}

		void TriangleRenderer2::initGL()
		{
			m_shader.init();
			m_vertexBuffer.init();
		}

		void TriangleRenderer2::initTriangles()
		{
			float stepWidth = 2 / float(NumTrianglesHorz);
			float stepHeight = 2 / float(NumTrianglesVert);
			Vector2f triangleSize(stepWidth, stepHeight);

			for (unsigned int i = 0; i < NumTrianglesHorz; i++) {
				for (unsigned int j = 0; j < NumTrianglesVert; j++) {
					Vector2f position = Vector2f(-1 + i * stepWidth + 0.5f * stepWidth, -1 + j * stepHeight + 0.5f * stepWidth);
					m_triangles.push_back(Triangle(Transform(position, triangleSize)));
				}
			}
		}

		void TriangleRenderer2::update()
		{
			m_transformedVertices.resize(getNumVertices());

			unsigned int counter = 0;
			for (std::size_t i = 0; i < m_triangles.size(); i++) {
				for (std::size_t j = 0; j < m_triangles[i].mesh.getSize(); j++) {
					m_transformedVertices[counter].position = m_triangles[i].transform * m_triangles[i].mesh[j].position;
					m_transformedVertices[counter].color = m_triangles[i].mesh[j].color;
					counter++;
				}
			}
		}

		std::size_t TriangleRenderer2::getNumVertices()
		{
			std::size_t numVertices = 0;
			for (std::size_t i = 0; i < m_triangles.size(); i++)
				numVertices += m_triangles[i].mesh.getSize();

			return numVertices;
		}

		void TriangleRenderer2::render()
		{
			// render1();
			render2();
			// render3();
		}

		void TriangleRenderer2::render1()
		{
			m_vertexBuffer.bind();
			m_vertexBuffer.setData(m_transformedVertices.size() * sizeof(Vertex), &(m_transformedVertices[0]), GL_DYNAMIC_DRAW);		
		}

		void TriangleRenderer2::render2()
		{
			m_vertexBuffer.bind();
			m_vertexBuffer.setData(m_transformedVertices.size() * sizeof(Vertex), NULL, GL_STREAM_DRAW);					// buffer orphaning
			m_vertexBuffer.setSubData(0, m_transformedVertices.size() * sizeof(Vertex), &(m_transformedVertices[0]));
		}

		void TriangleRenderer2::render3()
		{
			m_vertexBuffer.bind();
			m_vertexBuffer.setData(m_transformedVertices.size() * sizeof(Vertex), NULL, GL_STREAM_DRAW);		// buffer orphaning
			for (unsigned int i = 0; i < m_transformedVertices.size(); i++)										// buffer sub-updates
				m_vertexBuffer.setSubData(i * sizeof(Vertex) + offsetof(Vertex, position), sizeof(Vertex), &(m_transformedVertices[i].position));
		}

		void TriangleRenderer2::display()
		{
			prepareDisplay();
			glDrawArrays(GL_TRIANGLES, 0, m_transformedVertices.size());
			checkGLErrors();
		}

		void TriangleRenderer2::checkGLErrors()
		{
			GLuint error = glGetError();
			if (error != 0) {
				std::cout << error << std::endl;
				std::cin.get();
			}
		}

		void TriangleRenderer2::prepareDisplay()
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_shader.use();

			m_vertexBuffer.setVertexAttribPointer(m_shader.getAttributeLocation("a_vPosition"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			m_vertexBuffer.setVertexAttribPointer(m_shader.getAttributeLocation("a_vColor"), 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
			m_vertexBuffer.enable();
		}

		void TriangleRenderer2::close()
		{
			m_shader.destroy();
			m_window.destroy();
		}
	}
}

