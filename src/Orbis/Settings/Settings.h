#pragma once

// logging settings
// #define ORBIS_LOG_PERFORMANCE

// debugging settings
// #define ORBIS_DEBUG_GL
// #define ORBIS_DEBUG_RENDERDEVICE

// render settings
#define ORBIS_USE_TEXTURE_ATLASSING

// ensure valid settings combinations
#if defined(ORBIS_DEBUG_GL) && !defined(_DEBUG)
	#error ORBIS_DEBUG_GL is only valid in debug mode
#endif