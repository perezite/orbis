#pragma once

#include <string>

namespace System
{
	class Exception
	{
	public:
		Exception(const std::string &message) : _message(message) {}

		virtual ~Exception() throw() {}

		virtual const std::string &what() const throw() { return _message; }

		static void assert(bool condition, std::string message) { if (!condition) throw Exception(message); }

	protected:
		std::string _message;
	};
}