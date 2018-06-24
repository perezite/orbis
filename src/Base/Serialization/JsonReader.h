#pragma once

#include <string>
#include <sstream>

namespace Serialization
{
	// a representation of a json string as an object
	class JsonReader
	{
	public:
		// ctor
		JsonReader(std::string str);

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