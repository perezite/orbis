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
		const unsigned int TriangleRenderer2::NumTrianglesHorz = 2;
		const unsigned int TriangleRenderer2::NumTrianglesVert = 2;
		
		Window TriangleRenderer2::m_window;
		Shader TriangleRenderer2::m_shader;
		Stopwatch TriangleRenderer2::m_stopwatch;
		VertexBuffer TriangleRenderer2::m_vertexBuffer;
		std::vector<Vertex> TriangleRenderer2::m_vertices;
		std::vector<Vertex> TriangleRenderer2::m_transformedVertices;
		std::vector<Transform> TriangleRenderer2::m_transforms;

		void TriangleRenderer2::run()
		{
			m_window.init();
			initGL();
			initVertices();

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
			float stepWidth = 0.9f / float(NumTrianglesHorz);
			float stepHeight = 0.9f / float(NumTrianglesVert);
			Vector2f triangleSize(0.9f * stepWidth, 0.9f * stepHeight);

			for (unsigned int i = 0; i < NumTrianglesHorz; i++) {
				for (unsigned int j = 0; j < NumTrianglesVert; j++) {
					Vector2f position = Vector2f(i * stepWidth, j * stepHeight);
					Triangle triangle(Transform(position, triangleSize));
				}
			}
		}

		void TriangleRenderer2::initVertices()
		{
			m_vertices = {	Vertex{ Vector2f{ -0.5f,		-0.5f },		Color{ 1, 0, 0, 1 } },
							Vertex{ Vector2f{ 0,		-0.5f },		Color{ 0, 1, 0, 1 } },
							Vertex{ Vector2f{ -0.25f,	 0 },		Color{ 0, 0, 1, 1 } },
							Vertex{ Vector2f{ 0.5f,      0.5f },		Color{ 1, 0, 0, 1 } },
							Vertex{ Vector2f{ 0,		 0.5f },		Color{ 0, 1, 0, 1 } },
							Vertex{ Vector2f{ 0.25f,	 0 },		Color{ 0, 0, 1, 1 } } };
		}

		void TriangleRenderer2::update()
		{
			float alpha = fmod(m_stopwatch.getElapsedSeconds(), 2 * (float)M_PI);
			float ca = cosf(alpha), sa = sinf(alpha);

			m_transformedVertices.resize(m_vertices.size());
			for (std::size_t i = 0; i < m_vertices.size(); i++) {
				bool ccw = (i % 6) < 3;
				Vector2f pos = m_vertices[i].position;
				if (ccw)
					m_transformedVertices[i].position = Vector2f{ ca * pos.x - sa * pos.y,  sa * pos.x + ca * pos.y };
				else
					m_transformedVertices[i].position = Vector2f{ ca * pos.x + sa * pos.y, -sa * pos.x + ca * pos.y };
				m_transformedVertices[i].color = m_vertices[i].color;
			}
		}

		void TriangleRenderer2::render()
		{
			render1();
			render2();
			render3();
		}

		void TriangleRenderer2::render1()
		{
			m_vertexBuffer.bind();
			m_vertexBuffer.setData(m_transformedVertices.size() * sizeof(Vertex), &(m_transformedVertices[0]), GL_DYNAMIC_DRAW);		
		}

		void TriangleRenderer2::render2()
		{
			m_vertexBuffer.bind();
			m_vertexBuffer.setData(m_vertices.size() * sizeof(Vertex), NULL, GL_STREAM_DRAW);		// buffer orphaning
			m_vertexBuffer.setSubData(0, m_transformedVertices.size() * sizeof(Vertex), &(m_transformedVertices[0]));
		}

		void TriangleRenderer2::render3()
		{
			m_vertexBuffer.bind();
			m_vertexBuffer.setData(m_transformedVertices.size() * sizeof(Vertex), NULL, GL_STREAM_DRAW);		// buffer orphaning
			for (unsigned int i = 0; i < m_transformedVertices.size(); i++)									// buffer sub-updates
				m_vertexBuffer.setSubData(i * sizeof(Vertex) + offsetof(Vertex, position), sizeof(Vertex), &(m_transformedVertices[i].position));
		}

		void TriangleRenderer2::display()
		{
			prepareDisplay();

			glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

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

