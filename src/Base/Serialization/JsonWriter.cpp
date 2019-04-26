#include "JsonWriter.h"

#include "../System/Exception.h"
using namespace base;

#include <iomanip>

namespace base
{
	JsonWriter::JsonWriter()
	{
		beginChild();
	}

	void JsonWriter::beginChild()
	{
		m_is << (m_isFirstElement ? "" : ",");
		m_is << "{";
		m_isFirstElement = true;
	}

	void JsonWriter::endChild()
	{
		m_isFirstElement = false;
		m_is << "}";
	}

	void JsonWriter::addFloat(float value, int precision)
	{
		std::stringstream is;
		is << (m_isFirstElement ? "" : ",");
		is << std::fixed << std::setprecision(precision) << value << "f";
		m_is << is.rdbuf();
		m_isFirstElement = false;
	}

	std::string JsonWriter::toString()
	{
		endChild();
		std::string json = m_is.str();
		return json;
	}
}