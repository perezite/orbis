#pragma once

#include <sstream>
#include <string>

#define ORB_STRINGIFY(x) #x
#define ORB_TOSTRING(x) ORB_STRINGIFY(x)
#define ORB_ERROR() orb::Error(__FILE__, ORB_TOSTRING(__LINE__)).output()
#define ORB_ERROR_IF(condition) if (condition) ORB_ERROR()

namespace orb
{
	class Error
	{
	public:
		Error(std::string file, std::string line)
			: m_file(file), m_line(line)
		{ }

		std::ostream& output() { return m_output; };

		virtual ~Error();

	private:
		std::string m_file;

		std::string m_line;

		std::ostringstream m_output;
	};
}