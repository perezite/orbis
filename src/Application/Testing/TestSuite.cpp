#include "../Levels/Level1.h"
#include "../Levels/Level2.h"
#include "../Levels/Level3.h"
#include "../Levels/Level5.h"
#include "../Levels/Level6.h"
#include "../Levels/Level8.h"
#include "../Levels/Level9.h"


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

		overallSuccess &= TestRunner::executeTestcase(new Level1(), 20, "Level1");
		overallSuccess &= TestRunner::executeTestcase(new Level2(), 20, "Level2");
		overallSuccess &= TestRunner::executeTestcase(new Level3(), 20, "Level3");
		overallSuccess &= TestRunner::executeTestcase(new Level5(), 20, "Level5");
		overallSuccess &= TestRunner::executeTestcase(new Level6(), 20, "Level6");
		overallSuccess &= TestRunner::executeTestcase(new Level8(), 20, "Level8");
		overallSuccess &= TestRunner::executeTestcase(new Level9(), 20, "Level9");

		if (overallSuccess == false)
			LogUtil::showMessageBox("There were test failures. Check the log for more details", "Test failures");
		else
			LogUtil::showMessageBox("All tests passed", "Tests successful");
	}
}