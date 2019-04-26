#pragma once

#include "../System/StringUtil.h"

#include <string>
#include <sstream>
#include <vector>

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

		// add a float
		void addFloat(float value, int precision = 6);

		// get the json string
		std::string toString();

		// get a vector as json
		template <class T>
		static std::string toJson(std::vector<T> v);

	protected:
		void removeLeadingCommas(std::string& json);

	private:
		// the stringstream
		std::stringstream m_is;

		// is the next element the first element in the current node
		bool m_isFirstElement;
	};

	template <class T>
	std::string JsonWriter::toJson(std::vector<T> v)
	{
		return "{ " + StringUtil::join(v, ",") + " }";
	}
}

