#pragma once

#ifdef  WIN32
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#else
#include <GLES2/gl2.h>	
#include <GLES2/gl2ext.h>
#endif
#include <iostream>

#ifdef _DEBUG
	#define SB_GL_CHECK(cmd)  										\
		glGetError();												\
		cmd;														\
		{															\
			int error = glGetError();								\
			if (error != GL_NO_ERROR) {								\
				std::cout << "GL Error: " << error << std::endl;	\
				std::cin.get();										\
			}														\
		} 	
		
#else
	#define SB_GL_CHECK(cmd) cmd
#endif