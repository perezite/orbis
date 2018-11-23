#include "TriangleRenderer2.h"
#include <iostream>
#include <stddef.h>

namespace sb 
{
	namespace triangleRenderer2 
	{
		const unsigned int TriangleRenderer2::NumTrianglesHorz = 100;
		const unsigned int TriangleRenderer2::NumTrianglesVert = 100;
		
		Window TriangleRenderer2::m_window;
		Shader TriangleRenderer2::m_shader;
		std::vector<Triangle> TriangleRenderer2::m_triangles;
		GraphicsBuffer TriangleRenderer2::m_buffer;
		std::vector<Vertex> TriangleRenderer2::m_vertices;
		std::vector<GLushort> TriangleRenderer2::m_indices;
		bool TriangleRenderer2::m_indicesNeedUpdate = true;

		void TriangleRenderer2::run()
		{
			m_window.init(1500, 800);
			SDL_GL_SetSwapInterval(0);
			initGL();
			initTriangles();

			while (!m_window.hasQuitEvent()) {
				logPerformance();
				m_window.update();
				render();
				display();
				m_window.flip();
			}

			close();
		}

		void TriangleRenderer2::initGL()
		{
			m_shader.init();
			m_buffer.init();
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

		void TriangleRenderer2::logPerformance()
		{
			static Stopwatch stopwatch;
			static unsigned int frames = 0;

			float elapsed = stopwatch.getElapsedSeconds();
			frames++;
			if (elapsed > 1.0f) {
				float fps = frames / elapsed;
				SDL_Log("FPS: %f", fps);
				frames = 0;
				stopwatch.reset();
			}
		}

		void TriangleRenderer2::render()
		{
			calcVertices();
			if (m_indicesNeedUpdate)
				calcIndices();
			setupBuffer();

			m_indicesNeedUpdate = false;
		}

		void TriangleRenderer2::calcVertices()
		{
			m_vertices.resize(getNumVertices());

			unsigned int counter = 0;
			for (std::size_t i = 0; i < m_triangles.size(); i++) {
				for (std::size_t j = 0; j < m_triangles[i].mesh.getVertexCount(); j++) {
					m_vertices[counter].position = m_triangles[i].transform * m_triangles[i].mesh[j].position;
					m_vertices[counter].color = m_triangles[i].mesh[j].color;
					counter++;
				}
			}
		}

		std::size_t TriangleRenderer2::getNumVertices()
		{
			std::size_t numVertices = 0;
			for (std::size_t i = 0; i < m_triangles.size(); i++)
				numVertices += m_triangles[i].mesh.getVertexCount();

			return numVertices;
		}

		void TriangleRenderer2::calcIndices()
		{
			m_indices.resize(getNumIndices());

			unsigned int counter = 0;
			unsigned int offset = 0;
			for (std::size_t i = 0; i < m_triangles.size(); i++) {
				const std::vector<GLuint>& indices = m_triangles[i].mesh.getIndices();
				for (std::size_t j = 0; j < m_triangles[i].mesh.getIndexCount(); j++) {
					m_indices[counter] = indices[j] + offset;
					counter++;
				}
				offset += m_triangles[i].mesh.getVertexCount();
			}
		}

		std::size_t TriangleRenderer2::getNumIndices()
		{
			std::size_t numIndices = 0;
			for (std::size_t i = 0; i < m_triangles.size(); i++)
				numIndices += m_triangles[i].mesh.getIndexCount();

			return numIndices;
		}

		void TriangleRenderer2::setupBuffer()
		{
			m_buffer.bindVertexBuffer();
			m_buffer.setVertexData(m_vertices.size() * sizeof(Vertex), &(m_vertices[0]), GL_DYNAMIC_DRAW);		
			m_buffer.bindIndexBuffer();
			if (m_indicesNeedUpdate) {
				m_buffer.setIndexData(m_indices.size() * sizeof(GLushort), m_indices.data(), GL_STATIC_DRAW);
			}
		}

		void TriangleRenderer2::display()
		{
			prepareDisplay();
			m_buffer.enable();
			glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, 0);
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

			m_buffer.setVertexAttribPointer(m_shader.getAttributeLocation("a_vPosition"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			m_buffer.setVertexAttribPointer(m_shader.getAttributeLocation("a_vColor"), 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
		}

		void TriangleRenderer2::close()
		{
			m_shader.destroy();
			m_window.destroy();
		}
	}
}

