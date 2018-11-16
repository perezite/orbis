#pragma once

#include "Window.h"
#include "Triangle.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Stopwatch.h"

#include <string>
#include <map>
#include <vector>

namespace sb 
{
	namespace triangleRenderer2 
	{
		// This sandbox implements the triangle with vertex buffers and vertex array objects. 
		// References:	https://learnopengl.com/Getting-started/Hello-Triangle
		//				https://www.youtube.com/watch?v=ImtWD_9OAeY&t=2s
		//				http://www.learnopengles.com/android-lesson-seven-an-introduction-to-vertex-buffer-objects-vbos/
		class TriangleRenderer2
		{
		public:
			static const unsigned int NumTrianglesHorz;
			static const unsigned int NumTrianglesVert;

		public:
			static void run();

		protected:
			static void createWindow();

			static void initGL();

			static void initTriangles();

			static void initVertices();

			static void update();

			static void render();

			static void render1();

			static void render2();

			static void render3();

			static void display();

			static void prepareDisplay();

			static void close();

		private:
			static Window m_window;

			static Shader m_shader;

			static Stopwatch m_stopwatch;

			static VertexBuffer m_vertexBuffer;

			static std::vector<Vertex> m_vertices;

			static std::vector<Triangle> m_triangles;

			static std::vector<Vertex> m_transformedVertices;

			static std::vector<Transform> m_transforms;

		};
	}
}