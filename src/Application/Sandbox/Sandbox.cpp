#include "Sandbox.h"

#ifdef __SANDBOX__

#include "../../Base/Math/Vector2D.h"
using namespace Math;

#include <SDL2/SDL.h>
#ifdef __ANDROID__
	#include <GLES2/gl2.h>	
	#include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
	#include <gl/glew.h>
	#include <SDL2/SDL_opengl.h>
	#include <gl/glu.h>
#endif

#include <vector>
#include <iostream>

// shader program
int32_t shaderProgram = 0;

int height;
int width;

static const int32_t POSITION_PARAMETER_INDEX = 0;
static const int32_t COLOR_PARAMETER_INDEX = 1;

GLuint LoadShader(const char *shaderSrc, GLenum type)
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);
	if (shader != 0)
	{
		// Load the shader source
		glShaderSource(shader, 1, &shaderSrc, NULL);

		// Compile the shader
		glCompileShader(shader);
		// Check the compile status
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char* infoLog = new char[infoLen];
				glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
				std::cout << "Error compiling shader:" << std::endl << infoLog << std::endl;
				delete[] infoLog;
			}
			glDeleteShader(shader);
			shader = 0;
		}
	}
	return shader;
}

static int init() {
	// Initialize GL state.
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	char vShaderStr[] =
		"attribute vec4 a_vPosition;	\n"
		"attribute vec4 a_vColor;		\n"
		"varying vec4 v_vColor;			\n"
		"void main()					\n"
		"{								\n"
		"   gl_Position = a_vPosition;	\n"
		"	v_vColor = a_vColor;		\n"
		"}								\n";

	char fShaderStr[] =
		"#version 130				                \n"
		"precision mediump float;                   \n"
		"varying vec4 v_vColor;		 				\n"
		"void main()                                \n"
		"{                                          \n"
		"   gl_FragColor = v_vColor;				\n"
		"}                                          \n";

	GLuint vertexShader;
	GLuint fragmentShader;
	GLint linked;

	// Load the vertex/fragment shaders
	vertexShader = LoadShader(vShaderStr, GL_VERTEX_SHADER);
	fragmentShader = LoadShader(fShaderStr, GL_FRAGMENT_SHADER);

	// Create the program object
	shaderProgram = glCreateProgram();
	if (shaderProgram == 0)
	{
		return -1;
	}

	// Attach shaders to program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Bind a_vPosition to attribute 0 and a_vColor to 1
	glBindAttribLocation(shaderProgram, POSITION_PARAMETER_INDEX, "a_vPosition");
	glBindAttribLocation(shaderProgram, COLOR_PARAMETER_INDEX, "a_vColor");

	// Link the program
	glLinkProgram(shaderProgram);

	// Check the link status
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = new char[infoLen];
			glGetProgramInfoLog(shaderProgram, infoLen, NULL, infoLog);

			delete[] infoLog;
		}

		glDeleteProgram(shaderProgram);
		return -1;
	}

	return 0;
}

static void display()
{
	static const int32_t PositionNumElements = 3;
	static const int32_t ColorNumElements = 4;
	static const int32_t VertexSize = sizeof(GLfloat) * (PositionNumElements + ColorNumElements);

	glViewport(0, 0, width, height);
	glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(shaderProgram);

	glEnableVertexAttribArray(POSITION_PARAMETER_INDEX);
	glEnableVertexAttribArray(COLOR_PARAMETER_INDEX);

	// compute time delta in seconds
	static Uint32 previousTicks = SDL_GetTicks();
	Uint32 currentTicks = SDL_GetTicks();
	Uint32 elapsedTicks = currentTicks - previousTicks;
	previousTicks = SDL_GetTicks();
	float deltaTime = (float)elapsedTicks / 1000.0f;

	// set untransformed points
	const float z = 0.0f;
	Vector2D leftPoint(-0.3f, -0.3f);
	Vector2D rightPoint(0.3f, -0.3f);
	Vector2D topPoint(0.0f, 0.3f);

	// compute rotated points
	float omega = (float)M_PI;
	static float alpha = 0.0f;
	alpha += omega * deltaTime;
	Vector2D rotatedLeftPoint(cos(alpha)*leftPoint.GetX() - sin(alpha)*leftPoint.GetY(), sin(alpha)*leftPoint.GetX() + cos(alpha)*leftPoint.GetY());
	Vector2D rotatedRightPoint(cos(alpha)*rightPoint.GetX() - sin(alpha)*rightPoint.GetY(), sin(alpha)*rightPoint.GetX() + cos(alpha)*rightPoint.GetY());
	Vector2D rotatedTopPoint(cos(alpha)*topPoint.GetX() - sin(alpha)*topPoint.GetY(), sin(alpha)*topPoint.GetX() + cos(alpha)*topPoint.GetY());

	// render
	const float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat triangle[] = { rotatedTopPoint.GetX(), rotatedTopPoint.GetY(), z,
		color[0], color[1], color[2], color[3],
		rotatedLeftPoint.GetX(), rotatedLeftPoint.GetY(), z,
		color[0], color[1], color[2], color[3],
		rotatedRightPoint.GetX(), rotatedRightPoint.GetY(), z,
		color[0], color[1], color[2], color[3] };

	glVertexAttribPointer(POSITION_PARAMETER_INDEX, PositionNumElements, GL_FLOAT, GL_FALSE, VertexSize, triangle);
	glVertexAttribPointer(COLOR_PARAMETER_INDEX, ColorNumElements, GL_FLOAT, GL_FALSE, VertexSize, &triangle[3]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(POSITION_PARAMETER_INDEX);
	glDisableVertexAttribArray(COLOR_PARAMETER_INDEX);
}

void Run()
{
	SDL_Window* sdlWindow;
	SDL_GLContext glContext;

	// initialize
	width = height = 400;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	sdlWindow = SDL_CreateWindow("ExampleGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 400, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	glContext = SDL_GL_CreateContext(sdlWindow);
	glewInit();
	SDL_GL_SetSwapInterval(1);
	init();

	// main loop
	bool quit = false;
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
	}

	// cleanup
	glDeleteProgram(shaderProgram);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}


#endif