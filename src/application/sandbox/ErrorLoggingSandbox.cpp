#include "ErrorLoggingSandbox.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#define ORB_STRINGIFY(x) #x
#define ORB_TOSTRING(x) ORB_STRINGIFY(x)
#define ORB_ERROR() app::Error(__FILE__, ORB_TOSTRING(__LINE__)).output()

namespace app
{
	class Error
	{
	public:
		Error(std::string file, std::string line) 
			: m_file(file), m_line(line)
		{ }

		std::ostream& output() { return m_output; };

		// disable the VC warning 'destructor never returns, potential memory leak'. We want the error handling to be a one-liner so we have to call exit() in the destructor at this point...
		#pragma warning( push )
		#pragma warning( disable : 4722)
		virtual ~Error() {
			std::ostringstream os;
			os << m_file << " (" << m_line << "): " << m_output.str();

			std::string message = os.str();
			std::cout << message << std::endl;

			#ifdef _DEBUG
				throw message;
			#else
				std::cin.get();
				exit(1);
			#endif
		}
		#pragma warning( pop ) 

	private:
		std::string m_file;

		std::string m_line;

		std::ostringstream m_output;
	};

	void ErrorLoggingSandbox::run()
	{
		ORB_ERROR() << "Ooops, an error happened";

		std::cin.get();
	}
}
