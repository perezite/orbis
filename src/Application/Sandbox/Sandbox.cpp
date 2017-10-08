#include "Sandbox.h"

#ifdef __SANDBOX__

#include "../../Orbis/GUI/GUIHelper.h"
using namespace GUI;

#include <SDL2\SDL.h>
// #include <SDL2\SDL_image.h>
#ifdef WIN32
#include <gl\glew.h>
#include <SDL2\SDL_opengl.h>
#include <gl\glu.h>
#endif
#ifdef __ANDROID__
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif 
#include <stdio.h>
#include <string>
#include <iostream>

void init();
void initGL();
void render();
void close();

#ifdef WIN32
const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;
#endif

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
	"precision highp float;			\n \
	varying vec2 v_texCoord;		\n \
	uniform sampler2D s_texture;	\n \
									\n \
	void main()						\n \
	{								\n \
		gl_FragColor = texture2D(s_texture, v_texCoord);  \n \
	}";

/* gl_FragColor = texture2D(s_texture, v_texCoord);  \n \ */

SDL_Window* gWindow = NULL;
SDL_GLContext gContext;
GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLint gTexCoordinateLocation = -1;
GLint gSamplerLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;
GLuint gTexture = 0;

SDL_Surface* flipSDLSurface(SDL_Surface* surface)
{
	SDL_Surface *flipped = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
		surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

	// lock
	if (SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);
	if (SDL_MUSTLOCK(flipped))
		SDL_LockSurface(flipped);

	// copy flipped
	for (int row = surface->h - 1; row >= 0; row--)
	{
		for (int col = 0; col < surface->w; col++)
		{
			size_t sourceOffset = row * surface->w + col;
			size_t sourceOffsetBytes = sourceOffset * surface->format->BytesPerPixel;
			size_t destOffset = (surface->h - row - 1) * surface->w + col;
			size_t destOffsetBytes = destOffset * surface->format->BytesPerPixel;

			memcpy((char*)flipped->pixels + destOffsetBytes, (char*)surface->pixels + sourceOffsetBytes, surface->format->BytesPerPixel);
		}
	}

	// unlock
	if (SDL_MUSTLOCK(flipped))
		SDL_UnlockSurface(flipped);
	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);

	return flipped;
}

SDL_Surface* randomImage()
{
	SDL_Surface* image = SDL_CreateRGBSurface(SDL_SWSURFACE, 256, 256, 32,
		0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

	if (SDL_MUSTLOCK(image))
		SDL_LockSurface(image);

	unsigned int bytesPerPixel = image->format->BytesPerPixel;

	for (int i = 0; i < image->w * image->h; i++)
	{
		for (unsigned int j = 0; j < bytesPerPixel; j++)
		{
			char randomValue = rand() % 255;
			char* modifiedByte = (char*)image->pixels + i * bytesPerPixel + j;
			*modifiedByte = randomValue;
		}
	}

	if (SDL_MUSTLOCK(image))
		SDL_UnlockSurface(image);

	return image;
}

int loadTexture(std::string filePath, bool flipVertically = false)
{
	// SDL_Surface* img = IMG_Load(filePath.c_str());
	SDL_Surface* img = randomImage();
	SDL_Surface* img2 = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_ABGR8888, SDL_SWSURFACE);
	SDL_FreeSurface(img);
	img = img2;

	if (flipVertically)
	{
		SDL_Surface* flipped = flipSDLSurface(img);
		SDL_FreeSurface(img);
		img = flipped;
	}

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
	SDL_FreeSurface(img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return texture;
}

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
				GUIHelper::ShowMessageBox(infoLog, "Shader error");
				delete[] infoLog;
			}
			glDeleteShader(shader);
			shader = 0;
		}
	}
	return shader;
}

void init()
{
#ifdef WIN32
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	gContext = SDL_GL_CreateContext(gWindow);
	GLenum glewError = glewInit();
	initGL();
#endif
#ifdef __ANDROID__
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(0, 0, &mode);
	gWindow = SDL_CreateWindow(NULL, 0, 0, mode.w, mode.h, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
	gContext = SDL_GL_CreateContext(gWindow);
	initGL();
#endif

}

void initGL()
{
	gProgramID = glCreateProgram();

	GLuint vertexShader = LoadShader(vertexShaderSource, GL_VERTEX_SHADER);
	glAttachShader(gProgramID, vertexShader);

	GLuint fragmentShader = LoadShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	glAttachShader(gProgramID, fragmentShader);

	glLinkProgram(gProgramID);
	glUseProgram(gProgramID);

	gVertexPos2DLocation = glGetAttribLocation(gProgramID, "a_vPosition");
	int test = glGetError();
	gTexCoordinateLocation = glGetAttribLocation(gProgramID, "a_texCoord");
	gSamplerLocation = glGetUniformLocation(gProgramID, "s_texture");

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	GLfloat vertexData[] =
	{
		-0.5f, -0.5f,	// left bottom pos
		0.0f,  0.0f,	// left bottom tex
		0.5f, -0.5f,	// right bottom pos
		1.0f,  0.0f,	// right bottom tex
		-0.5f,  0.5f,	// left top pos pos
		0.0f,  1.0f,	// left top tex
		0.5f,  0.5f,	// right top pos
		1.0f,  1.0f	// right top tex
	};

	GLuint indexData[] = { 0, 1, 2, 2, 1, 3 };

	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * 8 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &gIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

	gTexture = loadTexture("D:\\Indie\\Development\\Simulo\\orbis\\bin\\Assets\\TestTransparent.png", true);
	glBindTexture(GL_TEXTURE_2D, gTexture);
	glUseProgram(0);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(gProgramID);

	glEnableVertexAttribArray(gVertexPos2DLocation);
	glEnableVertexAttribArray(gTexCoordinateLocation);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(gSamplerLocation, 0);

	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), NULL);
	glVertexAttribPointer(gTexCoordinateLocation, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), (void*)(0 + 2 * sizeof(GL_FLOAT)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

	glDisableVertexAttribArray(gTexCoordinateLocation);
	glDisableVertexAttribArray(gVertexPos2DLocation);
	glDisable(GL_TEXTURE_2D);
	glUseProgram(0);
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
			if (e.type == SDL_QUIT || e.type == SDL_KEYDOWN || e.type == SDL_FINGERDOWN)
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