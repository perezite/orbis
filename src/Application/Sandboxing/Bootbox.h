#pragma once

#define __SANDBOX__

#include "../../Orbis/Libraries/GL.h"

#include <vector>

namespace Sandboxing
{
	struct BEntity
	{
		float positionX;
		float positionY;
		float extent;
		bool isGrowing;
		GLuint texture;
	};

	// a class for bootstrapping code from the original sandbox class
	class Bootbox
	{
	public:
		static void Run();

	protected:
		static void Render();

		static void InitGL();

		static void InitIndexArray();

		static void InitEntities();

		static void InitTextures();

		static void UpdateEntities();

		static void UpdateVertexArray();

		static int FindLastEntityByTexture(GLuint texture);

	private:
		static GLint m_positionHandle;
		static GLint m_texCoordHandle;
		static GLint m_samplerHandle;
		static std::vector<GLuint> m_textures;
		static std::vector<GLfloat> m_vertices;
		static std::vector<GLushort> m_indices;
		static std::vector<BEntity> m_entities;
		static const int NUM_SPRITES;
		static const int VERTICES_PER_SPRITE;
		static const int INDICES_PER_SPRITE;
		static const float MIN_BLOCK_EXTENT;
		static const float MAX_BLOCK_EXTENT;
	};
}