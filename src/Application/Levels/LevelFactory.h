#pragma once

#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Level6.h"
#include "Level7.h"
#include "Level8.h"
#include "Level9.h"
#include "Level10.h"

#include "../../Base/System/Exception.h"
using namespace System;

#include <string>

namespace Levels
{
	class LevelFactory
	{
	public: 
		static Level* Instantiate(std::string name)
		{
			if (name == "Level1")
				return new Level1();
			else if (name == "Level2")
				return new Level2();
			else if (name == "Level3")
				return new Level3();
			else if (name == "Level4")
				return new Level4();
			else if (name == "Level5")
				return new Level5();
			else if (name == "Level6")
				return new Level6();
			else if (name == "Level7")
				return new Level7();
			else if (name == "Level8")
				return new Level8();
			else if (name == "Level9")
				return new Level9();
			else if (name == "Level10")
				return new Level10();

			throw new Exception("The level " + name + " is not registered");
		}
	};
}