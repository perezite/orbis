#include "PrimitiveType.h"

namespace orb
{
	class Mesh
	{
	public:
		Mesh(PrimitiveType primitiveType);

		virtual ~Mesh() {};

	private:
		PrimitiveType m_primitiveType;

	};

}

