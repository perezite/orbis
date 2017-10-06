#include "Renderer.h"

#include "VideoManager.h"
#include "Shader.h"
using namespace Video;

#include "../../Base/System/Exception.h"
using namespace System;

namespace
{
	// the vertex buffer object
	GLuint gVBO = 0;

	// the index buffer object
	GLuint gIBO = 0;

	// the shader
	Shader* shader;
}

namespace Video
{	
	Renderer::Renderer()
	{
		shader = new Shader();

		glClearColor(0.f, 0.f, 0.f, 1.f);

		glGenBuffers(1, &gVBO);
		glGenBuffers(1, &gIBO);
	}

	Renderer::~Renderer()
	{
		delete shader;
	}

	void Renderer::AddGeometry(std::vector<Vector2D> vertices, int indices[])
	{
		float vertexData[] = { vertices[0].GetX(), vertices[0].GetY(), vertices[1].GetX(), vertices[1].GetY(), vertices[2].GetX(), vertices[2].GetY() };
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glBufferData(GL_ARRAY_BUFFER, 2 * 3 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indices, GL_STATIC_DRAW);
	}

	void Renderer::Render(float rotation)
	{
		VideoManager::GetInstance()->ClearScreen();

		shader->Use();
		glEnableVertexAttribArray(shader->GetPositionLocation());

		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glVertexAttribPointer(shader->GetPositionLocation(), 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);

		glDisableVertexAttribArray(shader->GetPositionLocation());
		shader->Unuse();
	}
}