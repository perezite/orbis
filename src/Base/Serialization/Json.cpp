#include "Json.h"

#include "../System/Exception.h"
using namespace System;

#include <algorithm>

namespace Serialization
{
	bool Json::getChild()
	{
		char r;

		while (!m_is.eof() && m_is.get(r)) {
			if (r == '{')
				return true;
		}

		return false;
	}

	float Json::getFloat()
	{
		std::string val = getElement();
		return (float)atof(val.c_str());
	}

	std::string Json::getElement()
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

	void Json::removeWhitespaces(std::string& str)
	{
		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
		str.erase(std::remove(str.begin(), str.end(), '\r'), str.end());
		str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	}
}
