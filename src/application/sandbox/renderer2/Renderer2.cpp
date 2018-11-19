#include "Renderer2.h"
#include <iostream>
#include <stddef.h>

namespace sb 
{
	namespace renderer2 
	{
		const unsigned int Renderer2::NumDrawablesHorz = 100;
		const unsigned int Renderer2::NumDrawablesVert = 100;

		Window Renderer2::m_window;
		Shader Renderer2::m_shader;
		std::vector<Drawable*> Renderer2::m_drawables;
		GraphicsBuffer Renderer2::m_graphicsBuffer;
		std::vector<Vertex> Renderer2::m_transformedVertices;
		std::vector<GLushort> Renderer2::m_indices;
		bool Renderer2::m_indicesNeedUpdate = true;

		void Renderer2::run()
		{
			m_window.init(1500, 800);
			initGL();
			initDrawables();

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
			m_graphicsBuffer.init();
		}
		
		void Renderer2::initDrawables()
		{
			float stepWidth = 2 / float(NumDrawablesHorz);
			float stepHeight = 2 / float(NumDrawablesVert);
			Vector2f size(stepWidth * 0.9f, stepHeight * 0.9f);

			unsigned int counter = 0;
			for (unsigned int i = 0; i < NumDrawablesHorz; i++) {
				for (unsigned int j = 0; j < NumDrawablesVert; j++) {
					Vector2f position = Vector2f(-1 + i * stepWidth + 0.5f * stepWidth, -1 + j * stepHeight + 0.5f * stepWidth);
					Drawable* drawable = counter % 2 == 0 ? 
						(Drawable*)new Triangle(Transform(position, size)) : 
						(Drawable*)new Rectangle(Transform(position, size));
					m_drawables.push_back(drawable);
					counter++;
				}
				counter++;
			}
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
			if (m_indicesNeedUpdate)
				updateIndices();
		}



		void Renderer2::updateVertices()
		{
			m_transformedVertices.resize(getNumVertices());

			unsigned int counter = 0;
			for (std::size_t i = 0; i < m_drawables.size(); i++) {
				for (std::size_t j = 0; j < m_drawables[i]->getMesh().getVertexCount(); j++) {
					m_transformedVertices[counter].position = m_drawables[i]->getTransform() * m_drawables[i]->getMesh()[j].position;
					m_transformedVertices[counter].color = m_drawables[i]->getMesh()[j].color;
					counter++;
				}
			}
		}
		
		void Renderer2::updateIndices()
		{
			m_indices.resize(getNumIndices());

			unsigned int counter = 0;
			unsigned int offset = 0;
			for (std::size_t i = 0; i < m_drawables.size(); i++) {
				Mesh mesh = m_drawables[i]->getMesh();
				const std::vector<GLuint>& indices = mesh.getIndices();
				for (std::size_t j = 0; j < mesh.getIndexCount(); j++) {
					m_indices[counter] = indices[j] + offset;
					counter++;
				}
				offset += m_drawables[i]->getMesh().getVertexCount();
			}
		}

		std::size_t Renderer2::getNumVertices()
		{
			std::size_t numVertices = 0;
			for (std::size_t i = 0; i < m_drawables.size(); i++)
				numVertices += m_drawables[i]->getMesh().getVertexCount();

			return numVertices;
		}
		
		std::size_t Renderer2::getNumIndices()
		{
			std::size_t numIndices = 0;
			for (std::size_t i = 0; i < m_drawables.size(); i++)
				numIndices += m_drawables[i]->getMesh().getIndexCount();

			return numIndices;
		}

		void Renderer2::render()
		{
			// render1();
			render2();
			m_indicesNeedUpdate = false;
		}

		void Renderer2::render1()
		{
			m_graphicsBuffer.bindVertexBuffer();
			m_graphicsBuffer.setVertexData(m_transformedVertices.size() * sizeof(Vertex), m_transformedVertices.data(), GL_DYNAMIC_DRAW);
			if (m_indicesNeedUpdate) {
				m_graphicsBuffer.bindIndexBuffer();
				m_graphicsBuffer.setIndexData(m_indices.size() * sizeof(GLushort), m_indices.data(), GL_STATIC_DRAW);
			}
		}

		void Renderer2::render2()
		{
			m_graphicsBuffer.bindVertexBuffer();
			m_graphicsBuffer.setVertexData(m_transformedVertices.size() * sizeof(Vertex), NULL, GL_STREAM_DRAW);					// buffer orphaning
			m_graphicsBuffer.setVertexSubData(0, m_transformedVertices.size() * sizeof(Vertex), m_transformedVertices.data());
			if (m_indicesNeedUpdate) {
				m_graphicsBuffer.bindIndexBuffer();
				m_graphicsBuffer.setIndexData(m_indices.size() * sizeof(GLushort), m_indices.data(), GL_STATIC_DRAW);				// buffer orphaning
			}
		}

		void Renderer2::display()
		{
			prepareDisplay();
			checkGLErrors();
			m_graphicsBuffer.enable();
			glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, 0);
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

			m_graphicsBuffer.setVertexAttribPointer(m_shader.getAttributeLocation("a_vPosition"), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			m_graphicsBuffer.setVertexAttribPointer(m_shader.getAttributeLocation("a_vColor"), 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, color)));
		}

		void Renderer2::close()
		{
			m_shader.destroy();
			m_window.destroy();
			destroyDrawables();
		}

		void Renderer2::destroyDrawables()
		{
			for (std::size_t i = 0; i < m_drawables.size(); i++)
				delete m_drawables[i];
		}
	}
}

