#include "Renderer2.h"
#include <iostream>
#include <stddef.h>

namespace sb 
{
	namespace renderer2 
	{
		const unsigned int Renderer2::NumTrianglesHorz = 230;
		const unsigned int Renderer2::NumTrianglesVert = 230;
		
		Window Renderer2::m_window;
		Shader Renderer2::m_shader;
		std::vector<Triangle> Renderer2::m_triangles;
		std::vector<Rectangle> Renderer2::m_rectangles;
		GraphicsBuffers Renderer2::m_graphicsBuffers;
		std::vector<Vertex> Renderer2::m_transformedVertices;
		std::vector<GLushort> Renderer2::m_indices;

		void Renderer2::run()
		{
			m_window.init(1500, 800);
			SDL_GL_SetSwapInterval(0);
			initGL();
			initTriangles();
			initRectangles();

			while (!m_window.hasQuitEvent()) {
				logPerformance();
				m_window.update();
				update();
				render();
				display();
				m_window.flip();
			}

			close();
		}

		void Renderer2::initGL()
		{
			m_shader.init();
			m_graphicsBuffers.init();
		}

		void Renderer2::initTriangles()
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

		void Renderer2::initRectangles()
		{
			m_rectangles.push_back(Rectangle(Transform(Vector2f(0.5f, 0.5f), Vector2f(0.5f, 0.5f))));
		}

		void Renderer2::logPerformance()
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

		void Renderer2::update()
		{
			updateVertices();
			updateIndices();
		}

		void Renderer2::updateVertices()
		{
			m_transformedVertices.resize(getNumVertices());

			unsigned int counter = 0;
			for (std::size_t i = 0; i < m_rectangles.size(); i++) {
				for (std::size_t j = 0; j < m_rectangles[i].mesh.getVertexCount(); j++) {
					m_transformedVertices[counter].position = m_rectangles[i].transform * m_rectangles[i].mesh[j].position;
					m_transformedVertices[counter].color = m_rectangles[i].mesh[j].color;
					counter++;
				}
			}
		}

		void Renderer2::updateIndices()
		{
			m_indices.resize(getNumIndices());

			unsigned int counter = 0;
			for (std::size_t i = 0; i < m_rectangles.size(); i++) {
				const std::vector<GLuint>& indices = m_rectangles[i].mesh.getIndices();
				m_indices.insert(m_indices.end(), indices.begin(), indices.end());
			}
		}

		//void Renderer2::update()
		//{
		//	m_transformedVertices.resize(getNumVertices());

		//	unsigned int counter = 0;
		//	for (std::size_t i = 0; i < m_triangles.size(); i++) {
		//		for (std::size_t j = 0; j < m_triangles[i].mesh.getVertexCount(); j++) {
		//			m_transformedVertices[counter].position = m_triangles[i].transform * m_triangles[i].mesh[j].position;
		//			m_transformedVertices[counter].color = m_triangles[i].mesh[j].color;
		//			counter++;
		//		}
		//	}
		//}

	/*	std::size_t Renderer2::getNumVertices()
		{
			std::size_t numVertices = 0;
			for (std::size_t i = 0; i < m_triangles.size(); i++)
				numVertices += m_triangles[i].mesh.getVertexCount();

			return numVertices;
		}
*/

		std::size_t Renderer2::getNumVertices()
		{
			std::size_t numVertices = 0;
			for (std::size_t i = 0; i < m_rectangles.size(); i++)
				numVertices += m_rectangles[i].mesh.getVertexCount();

			return numVertices;
		}

		std::size_t Renderer2::getNumIndices()
		{
			std::size_t numIndices = 0;
			for (std::size_t i = 0; i < m_rectangles.size(); i++)
				numIndices += m_rectangles[i].mesh.getIndexCount();

			return numIndices;
		}

		void Renderer2::render()
		{
			render1();
			 //render2();
		}

		void Renderer2::render1()
		{
			m_graphicsBuffers.bindVertexBuffer();
			m_graphicsBuffers.setVertexData(m_transformedVertices.size() * sizeof(Vertex), &(m_transformedVertices[0]), GL_DYNAMIC_DRAW);
			m_graphicsBuffers.bindIndexBuffer();
			m_graphicsBuffers.setIndexData(m_indices.size() * sizeof(GLushort), &(m_indices[0]), GL_DYNAMIC_DRAW);
		}

		void Renderer2::render2()
		{
			m_graphicsBuffers.bindVertexBuffer();
			m_graphicsBuffers.setVertexData(m_transformedVertices.size() * sizeof(Vertex), NULL, GL_STREAM_DRAW);	// buffer orphaning
			m_graphicsBuffers.setVertexSubData(0, m_transformedVertices.size() * sizeof(Vertex), &(m_transformedVertices[0]));
			m_graphicsBuffers.bindIndexBuffer();
			m_graphicsBuffers.setIndexData(6, NULL, GL_STREAM_DRAW);												// buffer orphaning
			m_graphicsBuffers.setIndexData(6, &(m_indices[0]), GL_STREAM_DRAW);
		}

		void Renderer2::display()
		{
			prepareDisplay();
			checkGLErrors();
			m_graphicsBuffers.enable();
			glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, 0);
			// glDrawArrays(GL_TRIANGLES, 0, m_transformedVertices.size());
			checkGLErrors();
		}

		void Renderer2::checkGLErrors()
		{
			GLuint error = glGetError();
			if (error != 0) {
				std::cout << error << std::endl;
				std::cin.get();
			}
		}

		void Renderer2::prepareDisplay()
		{
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_shader.use();

			m_graphicsBuffers.setVertexAttribPointer(m_shader.getAttributeLocation("a_vPosition"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			m_graphicsBuffers.setVertexAttribPointer(m_shader.getAttributeLocation("a_vColor"), 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
		}

		void Renderer2::close()
		{
			m_shader.destroy();
			m_window.destroy();
		}
	}
}

