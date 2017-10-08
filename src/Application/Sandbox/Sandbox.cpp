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

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 400;

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
	uniform sampler2D s_texture;	\n \
	void main()						\n \
	{								\n \
		gl_FragColor = texture2D(s_texture, v_texCoord);  \n\
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

SDL_Surface* flipSDLSurface(SDL_Surface* surface)
{
	SDL_Surface *flipped = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel,
		surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask);

	if (SDL_MUSTLOCK(surface))
		SDL_LockSurface(surface);

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

	if (SDL_MUSTLOCK(surface))
		SDL_UnlockSurface(surface);

	return flipped;
}

int loadTexture(std::string filePath, bool flipVertically = false)
{
	SDL_Surface* img = IMG_Load(filePath.c_str());
	SDL_Surface* img2 = SDL_ConvertSurfaceFormat(img, SDL_PIXELFORMAT_RGBA8888, SDL_SWSURFACE);
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, img->pixels);
	SDL_FreeSurface(img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

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
	glAttachShader(gProgramID, vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glAttachShader(gProgramID, fragmentShader);
			
	glLinkProgram(gProgramID);
	
	gVertexPos2DLocation = glGetAttribLocation(gProgramID, "a_vPosition");
	gTexCoordinateLocation = glGetAttribLocation(gProgramID, "a_texCoord");
	gSamplerLocation = glGetUniformLocation(gProgramID, "s_texture");

	glClearColor(1.f, 1.f, 1.f, 1.f);

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