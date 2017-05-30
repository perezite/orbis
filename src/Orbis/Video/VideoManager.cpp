#include "VideoManager.h"

#include "..\..\Base\System\Exception.h"
#include "..\..\Base\System\StringHelper.h"
using namespace System;

#include <iostream>

namespace Video
{
	VideoManager* VideoManager::GetInstance()
	{
		static VideoManager instance;

		return &instance;
	}

	VideoManager::VideoManager()
	{
	}

	VideoManager::~VideoManager()
	{
	}
}