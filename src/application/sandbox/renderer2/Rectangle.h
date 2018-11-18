#pragma once

#include "Drawable.h"

namespace sb
{
	namespace renderer2
	{
		class Rectangle : public Drawable
		{
		public:
			Rectangle()
			{ }

			Rectangle(const Transform& transform)
				: m_transform(transform)
			{ }

		public:
			const Mesh& getMesh() const { return m_mesh; }

			const Transform& getTransform() const { return m_transform; }

		private: 

			static const Mesh m_mesh;

			Transform m_transform;
		};
	}
}