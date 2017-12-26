#pragma once

#include "Component.h"

#include "../Video/Shader.h"
#include "../Video/Texture.h"
#include "../Video/Mesh_v2.h"
using namespace Video;

#include <iostream>

namespace Components
{
	// an abstract renderer component
	class Renderer : public Component
	{
	public:
		// ctor
		Renderer();

		// get the shader
		Shader* GetShader() const { return m_shader; }

		// get the texture
		Texture* GetTexture() const { return m_texture; }

		// get the mesh
		Mesh_v2* GetMesh() const { return m_mesh; }

		// set the shader
		void SetShader(Shader* shader) { m_shader = shader; }

		// set the texture
		void SetTexture(Texture* texture) { m_texture = texture; }

		// set the mesh
		void SetMesh(Mesh_v2* mesh) { m_mesh = mesh; }

		// check if renderer belongs to same batch as given renderer
		bool IsBatchEqualTo(Renderer* const other) const;

	private: 
		// the shader
		Shader* m_shader;

		// the texture
		Texture* m_texture;

		// the mesh
		Mesh_v2* m_mesh;
	};
}