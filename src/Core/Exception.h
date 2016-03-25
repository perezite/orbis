#pragma once

#include <string>

namespace Core
{
	class Exception
	{
	public:
		Exception(const std::string &message) : _message(message) {}

		virtual ~Exception() throw() {}

		virtual const std::string &what() const throw() { return _message; }

	protected:
		std::string _message;
	};
}