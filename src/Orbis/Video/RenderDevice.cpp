#include "RenderDevice.h"

#include "VideoManager.h"
#include "Shader.h"
using namespace Video;

#include "../Core/LogHelper.h"
#include "../Libraries/SDL.h"
#include "../Libraries/GL.h"
using namespace Core;
using namespace Libraries;

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

	// the texture handle
	GLuint gTexture = 0;

	// flip an SDL surface
	SDL_Surface* GetFlippedSDLSurface(SDL_Surface* surface)
	{
		SDL_Surface *flipped = SDL::CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
			surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

		// lock
		SDL::LockSurface(surface);
		SDL::LockSurface(flipped);

		// copy flipped
		for (int row = surface->h - 1; row >= 0; row--)
		{
			for (int col = 0; col < surface->w; col++)
			{
				size_t sourceOffset = row * surface->w + col;
				size_t sourceOffsetBytes = sourceOffset * surface->format->BytesPerPixel;
				size_t destOffset = (surface->h - row - 1) * surface->w + col;
				size_t destOffsetBytes = destOffset * surface->format->BytesPerPixel;

				memcpy((char*)flipped->pixels + destOffsetBytes, (char*)surface->pixels + sourceOffsetBytes, surface->format->BytesPerPixel);
			}
		}

		// unlock
		SDL::UnlockSurface(flipped);
		SDL::UnlockSurface(surface);

		return flipped;
	}

	int LoadTexture(std::string filePath, bool flipVertically = false)
	{
		SDL_Surface* img = SDL::LoadSurface(filePath.c_str());
		SDL_Surface* img2 = SDL::ConvertSurfaceFormat(img, SDL_PIXELFORMAT_ABGR8888, SDL_SWSURFACE);
		SDL::FreeSurface(img);
		img = img2;

		if (flipVertically)
		{
			SDL_Surface* flipped = GetFlippedSDLSurface(img);
			SDL::FreeSurface(img);
			img = flipped;
		}

		unsigned int texture;
		GL::GenerateTextures(1, &texture);
		GL::BindTexture(GL_TEXTURE_2D, texture);
		GL::TextureImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
		SDL::FreeSurface(img);
		GL::TextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		GL::TextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		return texture;
	}
}

namespace Video
{
	RenderDevice::RenderDevice()
	{
		shader = new Shader("Shaders/Diffuse.vs", "Shaders/Diffuse.frag");

		GL::ClearColor(0.f, 0.f, 0.f, 1.f);

		GL::GenerateBuffers(1, &gVBO);
		GL::GenerateBuffers(1, &gIBO);
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
		GL::BindBuffer(GL_ARRAY_BUFFER, gVBO);
		GL::BufferData(GL_ARRAY_BUFFER, 2 * 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

		GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
		GL::BufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


		#ifdef WIN32 
			gTexture = LoadTexture("D:\\Indie\\Development\\Simulo\\orbis\\bin\\Assets\\Textures\\TestTransparent.png", true);
		#endif
		#ifdef __ANDROID__
			gTexture = LoadTexture("Textures/TestTransparent.png", true);
		#endif
	}

	void RenderDevice::Render(Transform* transform)
	{
		VideoManager::GetInstance()->ClearScreen();

		// setup rendering
		GL::Enable(GL_BLEND);
		GL::BlendFunction(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// setup textures
		GL::BindTexture(GL_TEXTURE_2D, gTexture);
		GL::ActiveTexture(GL_TEXTURE0);

		// setup shader
		shader->Use();
		GL::EnableVertexAttributeArray(shader->GetPositionAttributeHandle());
		GL::EnableVertexAttributeArray(shader->GetTexCoordAttributeHandle());
		shader->SetSamplerUniform(0);
		shader->SetTransformUniform(transform->GetMatrix());

		// setup data
		GL::BindBuffer(GL_ARRAY_BUFFER, gVBO);
		GL::VertexAttributePointer(shader->GetPositionAttributeHandle(), 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(GLfloat), NULL);
		GL::VertexAttributePointer(shader->GetTexCoordAttributeHandle(), 2, GL_FLOAT, GL_FALSE, 2 * 2 * sizeof(GLfloat), (void*)(0 + 2 * sizeof(GL_FLOAT)));
		GL::BindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

		// render
		GL::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		// cleanup
		GL::DisableVertexAttribArray(shader->GetTexCoordAttributeHandle());
		GL::DisableVertexAttribArray(shader->GetPositionAttributeHandle());
		GL::BindTexture(GL_TEXTURE_2D, 0);
		GL::Disable(GL_BLEND);
		shader->Unuse();
	}
}