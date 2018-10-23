#include "TestSuite.h"

#include "TestRunner.h"

#include "../Levels/Level2.h"
#include "../Levels/Level3.h"

#include <iostream>

namespace app
{
	void TestSuite::run()
	{
		bool overallSuccess = true;

		overallSuccess &= TestRunner::executeTestcase(new Level2(), 3, "Level2");
		overallSuccess &= TestRunner::executeTestcase(new Level3(), 5, "Level3");

		if (overallSuccess == false)
			LogUtil::showMessageBox("There were test failures. Check the log for more details", "Test failures");
		else
			LogUtil::showMessageBox("All tests passed", "Tests successful");
	}
}