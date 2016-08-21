#pragma once

#include <iostream>

namespace Application
{
	class App
	{
	public:
		// constructor
		App();

		// destructor
		~App();

		// run the application
		void Run();

	private:
		std::string m_workingDirectoryAtStartup;
	};
}