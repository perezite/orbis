#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace Serialization
{
	// a representation of a json string as an object
	class Json
	{
	public:
		// ctor
		Json(std::string str)
		{
			removeWhitespaces(str);
			m_is << str;
			getChild();
		}

		// get child
		bool getChild();

		// get float element
		float getFloat();
	protected:
		// remove whitespaces
		void removeWhitespaces(std::string& str);

		// get string element
		std::string getElement();

	private:
		// the stringstream
		std::stringstream m_is;
	};
}