#include "../Components/Component.h"
using namespace orb::components;

namespace orb
{
	namespace inspectors
	{
		class Inspector
		{
		public:
			// default ctor
			Inspector() : m_parent(NULL) { }

			// ctor
			Inspector(Component* parent) : m_parent(parent) { };

			// start
			virtual void start() { };

			// update
			virtual void update() { };

			// render
			virtual void renderDebug() { };

			// set entity
			void setParent(Component* parent) { m_parent = parent; }

		private:
			// the parent component
			Component *m_parent;
		};		
	}
}