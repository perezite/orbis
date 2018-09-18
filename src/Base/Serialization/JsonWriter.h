#pragma once

#include <string>
#include <sstream>

namespace base
{
	// a class for writing json strings
	class JsonWriter
	{
	public:
		// ctor
		JsonWriter();

		// begin a child
		void beginChild();

		// end a child
		void endChild();

		// get the json string
		void addFloat(float value, int precision = 6);

		// get the json string
		std::string toString();

	protected:
		void removeLeadingCommas(std::string& json);

	private:
		// the stringstream
		std::stringstream m_is;

		// is the next element the first element in the current node
		bool m_isFirstElement;
	};
}