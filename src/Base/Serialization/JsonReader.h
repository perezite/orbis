#pragma once

#include <string>
#include <sstream>

namespace base
{
	// a class for reading json strings
	class JsonReader
	{
	public:
		// ctor
		JsonReader(std::string str);

		// get child
		bool getChild();

		// get float element
		float getFloat();

		// get an unsigned long long
		unsigned long long getULongLong();

		// does the json have a next element at the current nesting level
		bool hasNextElement() const { return m_hasNextElement; }

	protected:
		// remove whitespaces
		void removeWhitespaces(std::string& str);

		// get string element
		std::string getElement();

	private:
		// the stringstream
		std::stringstream m_is;

		// the converter stream
		std::istringstream m_convert;

		// has next element
		bool m_hasNextElement;
	};
}