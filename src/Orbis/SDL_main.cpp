#include "CheesyHelper.h"

#include "SDL2/SDL.h"
#ifdef __ANDROID__
    #include <GLES2/gl2.h>
    #include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
    #include <gl/glew.h>
    #include <SDL2/SDL_opengl.h>
    #include <gl/glu.h>
#endif

#include "../Base/Math/Vector2D.h"
#include "../Base/Math/MathHelper.h"
using namespace Math;

#include "../Orbis//Video/VideoManager.h"
#include "../Orbis/Video/RenderDevice.h"
using namespace Video;

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string>
#include <iostream>


#define _USE_MATH_DEFINES

// the render device
RenderDevice g_RenderDevice;

// shader program
int32_t shaderProgram = 0;

int height;
int width;

static void display()
{
    // compute time delta in seconds
    static Uint32 previousTicks = SDL_GetTicks();
    Uint32 currentTicks = SDL_GetTicks();
    Uint32 elapsedTicks = currentTicks - previousTicks;
    previousTicks = SDL_GetTicks();
    float deltaTime = (float)elapsedTicks / 1000.0f;

    // set untransformed points
    // const float z = 0.0f;
    Vector2D leftPoint(-0.3f, -0.3f);
    Vector2D rightPoint(0.3f, -0.3f);
    Vector2D topPoint(0.0f, 0.3f);

    // compute rotated points
    float omega = MathHelper::GetPi();
    static float alpha = 0.0f;
    alpha += omega * deltaTime;
    Vector2D rotatedLeftPoint(cos(alpha)*leftPoint.GetX() - sin(alpha)*leftPoint.GetY(), sin(alpha)*leftPoint.GetX() + cos(alpha)*leftPoint.GetY());
    Vector2D rotatedRightPoint(cos(alpha)*rightPoint.GetX() - sin(alpha)*rightPoint.GetY(), sin(alpha)*rightPoint.GetX() + cos(alpha)*rightPoint.GetY());
    Vector2D rotatedTopPoint(cos(alpha)*topPoint.GetX() - sin(alpha)*topPoint.GetY(), sin(alpha)*topPoint.GetX() + cos(alpha)*topPoint.GetY());

	g_RenderDevice.BeginPrimitive(RenderMode::Triangle);
		g_RenderDevice.SetVertex2D(rotatedLeftPoint);
		g_RenderDevice.SetVertex2D(rotatedRightPoint);
		g_RenderDevice.SetVertex2D(rotatedTopPoint);
	g_RenderDevice.EndPrimitive();
}

#ifdef __ANDROID__
int run(int argc, char* args[])
{  
	VideoManager::GetInstance()->Run();
	return 0;

	/*
    SDL_Window* window = 0;
    SDL_GLContext gl = 0;

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    
    std::string s = "This is a std::string";
    CheesyHelper::Log("%s\n", s.c_str());

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
   
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
	Vector2D windowResolution(mode.w, mode.h);


    window = SDL_CreateWindow(NULL, 0, 0, (int)windowResolution.GetX(), (int)windowResolution.GetY(), SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);

    if (window == 0)
    {
        CheesyHelper::Log("Failed to created window.");
        SDL_Quit();
        return 1;
    }

    gl = SDL_GL_CreateContext(window);
    
	g_RenderDevice.SetWindowResolution(windowResolution);
	g_RenderDevice.Initialize();
    
    Uint8 done = 0;
    SDL_Event event;
    while(!done)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN)
            {
                done = 1;
            }
        }

        display();
        SDL_GL_SwapWindow(window);
    }

    exit(0);
	*/
}

#endif

#ifdef WIN32

int run(int argc, char* args[])
{
    /*SDL_Window* sdlWindow;
    SDL_GLContext glContext;
	*/

    // initialize
	/*Vector2D windowResolution(400.0f, 400.0f);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    sdlWindow = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)windowResolution.GetX(), (int)windowResolution.GetY(), SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    glContext = SDL_GL_CreateContext(sdlWindow);
    glewInit();
    SDL_GL_SetSwapInterval(1);
	g_RenderDevice.SetWindowResolution(windowResolution);
	g_RenderDevice.Initialize();*/

    // main loop
    /*bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }

        display();
        SDL_GL_SwapWindow(sdlWindow);
    }*/


    // cleanup
    /*glDeleteProgram(shaderProgram);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();*/

	VideoManager::GetInstance()->Run();

    return 0;
}

#endif