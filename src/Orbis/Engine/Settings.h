#pragma once

// logging settings
#define ORBIS_LOG_PERFORMANCE

// debugging settings
// #define ORBIS_DEBUG_GL
// #define ORBIS_DEBUG_RENDERDEVICE

// video settings
#define ORBIS_USE_TEXTURE_ATLASSING
#define ORBIS_DESKTOP_DEFAULT_RESOLUTION (base::Vector2f(400, 711));

// ensure valid settings combinations
#if defined(ORBIS_DEBUG_GL) && !defined(_DEBUG)
	#error ORBIS_DEBUG_GL is only valid in debug mode
#endif