#include "Renderer2.h"
#include "PerformanceLogger.h"
#include "Logger.h"
#include <iostream>
#include <stddef.h>

namespace sb 
{
	namespace renderer2 
	{
		const unsigned int Renderer2::NumDrawablesHorz = 130;
		const unsigned int Renderer2::NumDrawablesVert = 130;

		Window Renderer2::m_window;
		Shader Renderer2::m_shader;
		std::vector<Actor*> Renderer2::m_actors;
		GraphicsBuffer Renderer2::m_graphicsBuffer;
		std::vector<Vertex> Renderer2::m_transformedVertices;
		std::vector<GLushort> Renderer2::m_indices;
		bool Renderer2::m_indicesNeedUpdate = true;

		void Renderer2::run()
		{
			m_window.init(1500, 800);
			init();

			while (!m_window.hasQuitEvent()) {
				PerformanceLogger::log();
				update();
				render();
				display();
				m_window.flip();
				m_window.update();
			}

			close();
		}

		void Renderer2::init()
		{
			initGL();
			initActors();
		}

		void Renderer2::initGL()
		{
			m_shader.init();
			m_graphicsBuffer.init();
		}
		
		void Renderer2::initActors()
		{
			float stepWidth = 2 / float(NumDrawablesHorz);
			float stepHeight = 2 / float(NumDrawablesVert);
			Vector2f size(stepWidth * 0.9f, stepHeight * 0.9f);

			unsigned int counter = 0;
			for (unsigned int i = 0; i < NumDrawablesHorz; i++) {
				for (unsigned int j = 0; j < NumDrawablesVert; j++) {
					Vector2f position = Vector2f(-1 + i * stepWidth + 0.5f * stepWidth, -1 + j * stepHeight + 0.5f * stepWidth);
					Actor* actor = counter % 2 == 0 ? 
						(Actor*)new Triangle(Transform(position, size)) : 
						(Actor*)new Rectangle(Transform(position, size));
					actor->omega = -2.0f + 4.0f * (float)(rand() % RAND_MAX) / (float)RAND_MAX;
					m_actors.push_back(actor);
					counter++;
				}
				counter++;
			}
		}

		void Renderer2::update()
		{
			static Stopwatch sw;

			for (std::size_t i = 0; i < m_actors.size(); i++)
				m_actors[i]->setRotation(sw.getElapsedSeconds() * m_actors[i]->omega);
		}

		void Renderer2::render()
		{
			updateVertices();
			if (m_indicesNeedUpdate)
				updateIndices();
			updateBuffers();
		}

		void Renderer2::updateVertices()
		{
			m_transformedVertices.resize(getNumVertices());

			unsigned int counter = 0;
			for (std::size_t i = 0; i < m_actors.size(); i++) {
				for (std::size_t j = 0; j < m_actors[i]->getMesh().getVertexCount(); j++) {
					m_transformedVertices[counter].position = m_actors[i]->getTransform() * m_actors[i]->getMesh()[j].position;
					m_transformedVertices[counter].color = m_actors[i]->getMesh()[j].color;
					counter++;
				}
			}
		}
		
		void Renderer2::updateIndices()
		{
			m_indices.resize(getNumIndices());

			unsigned int counter = 0;
			unsigned int offset = 0;
			for (std::size_t i = 0; i < m_actors.size(); i++) {
				Mesh mesh = m_actors[i]->getMesh();
				const std::vector<GLuint>& indices = mesh.getIndices();
				for (std::size_t j = 0; j < mesh.getIndexCount(); j++) {
					m_indices[counter] = indices[j] + offset;
					counter++;
				}
				offset += m_actors[i]->getMesh().getVertexCount();
			}
		}

		std::size_t Renderer2::getNumVertices()
		{
			std::size_t numVertices = 0;
			for (std::size_t i = 0; i < m_actors.size(); i++)
				numVertices += m_actors[i]->getMesh().getVertexCount();

			if (numVertices > USHRT_MAX + 1)
				Logger().error() << "Drawing more than " << USHRT_MAX + 1 << " vertices per frame is not supported at the moment" << std::endl;
	
			return numVertices;
		}
		
		std::size_t Renderer2::getNumIndices()
		{
			std::size_t numIndices = 0;
			for (std::size_t i = 0; i < m_actors.size(); i++)
				numIndices += m_actors[i]->getMesh().getIndexCount();

			return numIndices;
		}

		void Renderer2::updateBuffers()
		{
			m_graphicsBuffer.bindVertexBuffer();
			m_graphicsBuffer.setVertexData(m_transformedVertices.size() * sizeof(Vertex), NULL, GL_STREAM_DRAW);					// buffer orphaning
			m_graphicsBuffer.setVertexSubData(0, m_transformedVertices.size() * sizeof(Vertex), m_transformedVertices.data());
			if (m_indicesNeedUpdate) {
				m_graphicsBuffer.bindIndexBuffer();
				m_graphicsBuffer.setIndexData(m_indices.size() * sizeof(GLushort), m_indices.data(), GL_STATIC_DRAW);				// buffer orphaning
			}

			m_indicesNeedUpdate = false;
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
			GLuint errorCode = glGetError();
			if (errorCode != 0)
				Logger().error() << "OpenGL Error: " << errorCode << std::endl;
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
			destroyActors();
		}

		void Renderer2::destroyActors()
		{
			for (std::size_t i = 0; i < m_actors.size(); i++)
				delete m_actors[i];
		}
	}
}

