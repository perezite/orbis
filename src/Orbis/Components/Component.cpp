# include "Component.h"

namespace orb
{
	namespace components
	{
		Component::~Component()
		{
			if (m_inspector)
				delete m_inspector;
		}
		
		void Component::startComponent()
		{
			start();
			if (m_inspector)
				m_inspector->start();
		}
	}
}