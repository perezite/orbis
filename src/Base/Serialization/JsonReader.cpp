#include "JsonReader.h"

#include "../System/Exception.h"
using namespace System;

namespace Serialization
{
	JsonReader::JsonReader(std::string str)
	{
		removeWhitespaces(str);
		m_is << str;
		getChild();
	}

	bool JsonReader::getChild()
	{
		char r;

		while (!m_is.eof() && m_is.get(r)) {
			if (r == '{')
				return true;
		}

		return false;
	}

	float JsonReader::getFloat()
	{
		std::string val = getElement();
		return (float)atof(val.c_str());
	}

	std::string JsonReader::getElement()
	{
		char r;
		std::string buf;

		while (m_is.get(r)) {
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
