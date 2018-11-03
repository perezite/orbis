#include "VideoManager.h"

namespace orb
{
	VideoManager* VideoManager::instance()
	{
		static VideoManager instance;
		return &instance;
	}
}
