#include "TriangleRenderer.h"

#include "..\Core\TimeManager.h"
using namespace Core;

#include "..\Video\VideoManager.h"
using namespace Video;

#include "..\Game\Entity.h"
using namespace Game;

#include "..\..\Base\Math\MathHelper.h"
using namespace Math;

#include <SDL2\SDL.h>
#ifdef __ANDROID__
#include <GLES2/gl2.h>	
#include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
#include <gl/glew.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>
#endif

#include <math.h>
#include <iostream>

namespace
{
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	SDL_Window* gWindow = NULL;

	SDL_GLContext gContext;

	bool gRenderQuad = true;

	GLuint gProgramID = 0;
	GLint gVertexPos2DLocation = -1;
	GLuint gVBO = 0;
	GLuint gIBO = 0;

	void initGL()
	{
		gProgramID = glCreateProgram();
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* vertexShaderSource[] =
		{
			"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
		};
		glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
		glCompileShader(vertexShader);
		GLint vShaderCompiled = GL_FALSE;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
		glAttachShader(gProgramID, vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const GLchar* fragmentShaderSource[] =
		{
			"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 0.0, 0.0, 1.0 ); }"
		};
		glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);
		glAttachShader(gProgramID, fragmentShader);

		glLinkProgram(gProgramID);
		gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");

		glClearColor(0.f, 0.f, 0.f, 1.f);

		GLfloat vertexData[] =
		{
			-0.5f, -0.5f,
			0.5f, -0.5f,
			0.0f,  0.5f
		};

		GLuint indexData[] = { 0, 1, 2 };

		glGenBuffers(1, &gVBO);
		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glBufferData(GL_ARRAY_BUFFER, 2 * 3 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

		glGenBuffers(1, &gIBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
	}

	void init()
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		gContext = SDL_GL_CreateContext(gWindow);
		#ifdef WIN32
			GLenum glewError = glewInit();
		#endif
		initGL();
	}

	void render()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(gProgramID);
		glEnableVertexAttribArray(gVertexPos2DLocation);

		glBindBuffer(GL_ARRAY_BUFFER, gVBO);
		glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, NULL);

		glDisableVertexAttribArray(gVertexPos2DLocation);
		glUseProgram(NULL);
	}

	void close()
	{
		glDeleteProgram(gProgramID);

		SDL_DestroyWindow(gWindow);
		gWindow = NULL;

		SDL_Quit();
	}
}

namespace Components
{
	TriangleRenderer::~TriangleRenderer()
	{
		close();
	}

	void TriangleRenderer::Start()
	{
		VideoManager::GetInstance();
		initGL();
	}

	void TriangleRenderer::Render()
	{
		render();
	}

	/*
	void TriangleRenderer::Render()
	{
		// set untransformed points
		Vector2D leftPoint(-0.3f, -0.3f);
		Vector2D rightPoint(0.3f, -0.3f);
		Vector2D topPoint(0.0f, 0.3f);

		// compute rotated points
		static const float omega = MathHelper::GetPi();
		static float alpha = 0.0f;
		alpha += omega * TimeManager::GetInstance()->GetDeltaSeconds();

		// render
		Renderer* renderer = VideoManager::GetInstance()->GetRenderer();
		renderer->BeginPrimitive(RenderMode::Triangle);
			renderer->SetVertex2D(leftPoint);
			renderer->SetVertex2D(rightPoint);
			renderer->SetVertex2D(topPoint);
		renderer->EndPrimitive(alpha);
	}*/
}