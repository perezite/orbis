#pragma once

#ifdef  WIN32
	#include <gl/glew.h>
	#include <SDL2/SDL_opengl.h>
	#include <gl/glu.h>
#elif defined(__ANDROID__)
	#include <GLES2/gl2.h>	
	#include <GLES2/gl2ext.h>
#else
	#error Platform not supported
#endif 