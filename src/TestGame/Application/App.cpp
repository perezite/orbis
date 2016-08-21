#include "App.h"

#include <stdio.h>
#include <string>
#include <iostream>

#include "..\..\Base\System\EnvironmentHelper.h"
using namespace System;

#include "..\..\Base\System\Exception.h"
using namespace System;

#include "..\..\Orbis\Game\LevelManager.h"
using namespace Game;

#include "..\..\Orbis\Orbis\OrbisMain.h"
using namespace Orbis;

#include "..\Levels\Level1.h"
using namespace Levels;


namespace Application
{
	App::App()
	{
		m_workingDirectoryAtStartup = EnvironmentHelper::GetWorkingDirectory();

		std::string executableDirectoryPath = EnvironmentHelper::GetExecutableDirectoryPath();
		EnvironmentHelper::SetWorkingDirectory(executableDirectoryPath);
	}

	App::~App()
	{
		EnvironmentHelper::SetWorkingDirectory(m_workingDirectoryAtStartup);
	}

	void App::Run()
	{
		OrbisMain orbis(800, 400);

		Level *level1 = new Level1();
		LevelManager::GetInstance()->QueueLevel(level1);
		orbis.Run();
	}
}


