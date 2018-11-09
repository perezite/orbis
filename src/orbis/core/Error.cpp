#include "Error.h"
#include "Log.h"

namespace orb
{
	// disable the VC warning 'destructor never returns, potential memory leak'. We want the error handling to be a one-liner so we have to call exit() in the destructor at this point...
	#if defined(_MSC_VER) && defined(WIN32) 
		#pragma warning( push )
		#pragma warning( disable : 4722)
	#endif

	// disable VC warning 'function assumed not to throw an exception but does'
	#if defined(_MSC_VER) && defined(WIN32) && defined(_DEBUG) 
		#pragma warning( push )
		#pragma warning( disable: 4297)
	#endif

	Error::~Error() {
		std::ostringstream os;
		os << m_file << " (" << m_line << "): " << m_output.str();
		std::string message = os.str();

		Log().error() << message;

		#ifdef _DEBUG
			throw message;
		#else
			Log().errorMessageBox("Error") << message;
			exit(1);
		#endif
	}

	#if defined(_MSC_VER) && defined(WIN32) && defined(_DEBUG) 
		#pragma warning( pop ) 
	#endif

	#if defined(_MSC_VER) && defined(WIN32) 
		#pragma warning( pop ) 
	#endif
}
