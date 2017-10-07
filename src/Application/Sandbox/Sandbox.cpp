#include "Sandbox.h"

#ifdef __SANDBOX__
#ifdef WIN32

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <gl\glew.h>
#include <SDL2\SDL_opengl.h>
#include <gl\glu.h>
#include <stdio.h>
#include <string>

void init();
void initGL();
void render();
void close();

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const GLchar* vertexShaderSource =
	"attribute vec2 a_vPosition;	\n \
	attribute vec2 a_texCoord;		\n \
	varying vec2 v_texCoord;		\n \
									\n \
	void main()						\n \
	{								\n \
		gl_Position = vec4( a_vPosition.x, a_vPosition.y, 0, 1 ); \n \
		v_texCoord = a_texCoord;		\n \
	}";

const GLchar* fragmentShaderSource =
"varying vec2 v_texCoord;		\n \
	uniform sampler2D s_texture; \n \
	void main()						\n \
	{								\n \
		gl_FragColor = vec4(1, 0, 0, 1); \n\
	}";

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;
GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLint gTexCoordinateLocation = -1;
GLint gSamplerLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;
GLuint gTexture = 0;

int loadTexture(std::string filePath)
{
	SDL_Surface* img = IMG_Load(filePath.c_str());
	SDL_Surface* img2 = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_RGBA8888, SDL_SWSURFACE);
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img2->w, img2->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, img2->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	SDL_FreeSurface(img);
	SDL_FreeSurface(img2);
	return texture;
}

void init()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	gContext = SDL_GL_CreateContext(gWindow);
	GLenum glewError = glewInit();
	initGL();
}

void initGL()
{
	gProgramID = glCreateProgram();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	glAttachShader(gProgramID, vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glAttachShader(gProgramID, fragmentShader);
			
	glLinkProgram(gProgramID);
	
	gVertexPos2DLocation = glGetAttribLocation(gProgramID, "a_vPosition");
	gTexCoordinateLocation = glGetAttribLocation(gProgramID, "a_texCoord");
	gSamplerLocation = glGetUniformLocation(gProgramID, "s_texture");

	glClearColor(0.f, 0.f, 0.f, 1.f);

	GLfloat vertexData[] =
	{
		-0.5f, -0.5f,
		0.0f, 0.0f,
		0.5f, -0.5f,
		1.0f, 0.0f,
		0.0f, 0.5f,
		0.5f, 1.0f
	};

	GLuint indexData[] = { 0, 1, 2 };

	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * 6 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &gIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

	gTexture = loadTexture("D:\\Indie\\Development\\Simulo\\orbis\\bin\\Assets\\TestTransparent.png");
	glBindTexture(GL_TEXTURE_2D, gTexture);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(gProgramID);

	glEnableVertexAttribArray(gVertexPos2DLocation);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(gSamplerLocation, 0);

	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(gTexCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)(0 + 2 * sizeof(GL_FLOAT)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);

	glDisableVertexAttribArray(gVertexPos2DLocation);
	glDisable(GL_TEXTURE_2D);
	glUseProgram(NULL);
}

void close()
{
	glDeleteProgram(gProgramID);

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}

void run()
{
	init();

	bool quit = false;

	SDL_Event e;

	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		render();

		SDL_GL_SwapWindow(gWindow);
	}

	close();
}

#endif
#endif