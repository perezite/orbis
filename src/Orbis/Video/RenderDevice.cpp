#include "RenderDevice.h"

#include "VideoManager.h"
#include "Shader.h"
#include "Texture.h"
using namespace Video;

#include "../Core/LogHelper.h"
#include "../Libraries/SDL.h"
#include "../Libraries/GL.h"
#include "../Components/Camera.h"
using namespace Core;
using namespace Components;

#include "../../Base/System/Exception.h"
#include "../../Base/Math/Matrix4.h"
using namespace System;
using namespace Math;

namespace
{
	// the vertex buffer object
	GLuint gVBO = 0;

	// the index buffer object
	GLuint gIBO = 0;

	// the shader
	Shader* shader;

	// the texture 
	Texture* texture;
}

namespace Video
{
	RenderDevice::RenderDevice()
	{
		shader = new Shader("Shaders/Diffuse.vs", "Shaders/Diffuse.frag");
		texture = new Texture("Textures/TestTransparent.png");

		glClearColor(0.f, 0.f, 0.f, 1.f);

		glGenBuffers(1, &gVBO);
		glGenBuffers(1, &gIBO);
	}

	RenderDevice::~RenderDevice()
	{
		delete shader;
	}

	void RenderDevice::AddGeometry(std::vector<Vector2D> vertices, std::vector<Vector2D> texCoords, std::vector<int> indices)
	{
		float vertexData[] = { vertices[0].GetX(), vertices[0].GetY(), texCoords[0].GetX(), texCoords[0].GetY(),
			vertices[1].GetX(), vertices[1].GetY(), texCoords[1].GetX(), texCoords[1].GetY(),
			vertices[2].GetX(), vertices[2].GetY(), texCoords[2].GetX(), texCoords[2].GetY(),
			vertices[3].GetX(), vertices[3].GetY(), texCoords[3].GetX(), texCoords[3].GetY() };
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glBufferData(GL_ARRAY_BUFFER, 2 * 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
	}

	void RenderDevice::Render(Transform* transform)
	{
		VideoManager::GetInstance()->ClearScreen();

		// setup rendering
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// setup textures
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureHandle());
		glActiveTexture(GL_TEXTURE0);

		// setup shader
		shader->Use();
		glEnableVertexAttribArray(shader->GetPositionAttributeHandle());
		glEnableVertexAttribArray(shader->GetTexCoordAttributeHandle());
		shader->SetSamplerUniform(0);
		shader->SetModelViewMatrix(Camera::GetViewMatrix() * transform->GetMatrix());

		// setup data
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glVertexAttribPointer(shader->GetPositionAttributeHandle(), 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(GLfloat), NULL);
		glVertexAttribPointer(shader->GetTexCoordAttributeHandle(), 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(GLfloat), (void*)(0 + 2 * sizeof(GL_FLOAT)));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

		// render
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		// cleanup
		glDisableVertexAttribArray(shader->GetTexCoordAttributeHandle());
		glDisableVertexAttribArray(shader->GetPositionAttributeHandle());
		glDisable(GL_BLEND);
		shader->Unuse();
	}
}