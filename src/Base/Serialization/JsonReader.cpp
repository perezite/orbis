#include "JsonReader.h"

#include "../System/Exception.h"
using namespace base;

#include <stdlib.h>
#include <algorithm>

namespace base
{
	JsonReader::JsonReader(std::string str) : m_hasNextElement(true)
	{
		removeWhitespaces(str);
		m_is << str;
		getChild();
	}

	bool JsonReader::getChild()
	{
		char r;

		while (!m_is.eof() && m_is.get(r)) {
			if (r == '{') {
				m_hasNextElement = true;
				return true;
			}
		}

		return false;
	}

	float JsonReader::getFloat()
	{
		std::string val = getElement();
		return (float)atof(val.c_str());
	}

	unsigned long long JsonReader::getULongLong()
	{
		m_convert.clear();
		m_convert.str(getElement());
		unsigned long long result;
		m_convert >> result;
		return result;
	}

	std::string JsonReader::getElement()
	{
		char r;
		std::string buf;

		while (m_is.get(r)) {
			if (r == '}')
				m_hasNextElement = false;
			if (r == ',' || r == '}')
				return buf;
			buf.push_back(r);
		}

		throw Exception("Unable to read json");
	}

	void JsonReader::removeWhitespaces(std::string& str)
	{
		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
		str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	}
}