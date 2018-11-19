#pragma once

#include "Actor.h"

namespace sb
{
	namespace renderer2
	{
		class Triangle : public Actor
		{
		public:
			Triangle()
			{ }

			Triangle(const Transform& transform)
				: m_transform(transform)
			{ }
			
			void rotate(float dt);

		public:
			const Mesh& getMesh() const { return m_mesh; }

			Transform& getTransform() { return m_transform; }

		private:
			static const Mesh m_mesh;

			Transform m_transform;
		};
	}
}
