#pragma once

// only set this define for diagnosing opengl errors, do not use in release mode because it degrades performance severely
// #define GL_DIAGNOSTICS 

#ifdef __ANDROID__
	#include <GLES2/gl2.h>	
	#include <GLES2/gl2ext.h>
#endif 
#ifdef WIN32
	#include <gl/glew.h>
	#include <SDL2/SDL_opengl.h>
	#include <gl/glu.h>
#endif

void GL_dummy();

#if defined(GL_DIAGNOSTICS)

	void GL_Verify();

	GLuint GL_Verify(GLuint returnValue);

	GLint GL_Verify(GLint returnValue);

	#define GL_VERIFY(call) \
		call,				\
		GL_Verify()			

	GLenum GLEW_Verify(GLenum returnValue);

	#if defined(WIN32)
		#define GLEW_ORIGINAL(call) GLEW_GET_FUN(__glew ## call)
	#else
		#define GLEW_ORIGINAL(call) gl ## call
	#endif

	#define glGenTextures(n, textures) GL_VERIFY(glGenTextures(n, textures))

	#define glBindTexture(target, texture) GL_VERIFY(glBindTexture(target, texture))

	#define glTexImage2D(target, level, internalFormat, width, height, border, format, type, data) \
		GL_VERIFY(glTexImage2D(target, level, internalFormat, width, height, border, format, type, data))

	#define glTexParameteri(texture, pname, param) GL_VERIFY(glTexParameteri(texture, pname, param))

	#undef glActiveTexture
	#define glActiveTexture(texture) GL_VERIFY(GLEW_ORIGINAL(ActiveTexture)(texture))

	#undef glGenBuffers
	#define glGenBuffers(n, buffers) GL_VERIFY(GLEW_ORIGINAL(GenBuffers)(n, buffers))

	#undef glBindBuffer
	#define glBindBuffer(target, buffer) GL_VERIFY(GLEW_ORIGINAL(BindBuffer)(target, buffer))

	#undef glBufferData
	#define glBufferData(target, size, data, usage) GL_VERIFY(GLEW_ORIGINAL(BufferData)(target, size, data, usage))

	#define glEnable(cap) GL_VERIFY(glEnable(cap))

	#define glBlendFunc(sfactor, dfactor) GL_VERIFY(glBlendFunc(sfactor, dfactor))

	#undef glEnableVertexAttribArray
	#define glEnableVertexAttribArray(index) GL_VERIFY(GLEW_ORIGINAL(EnableVertexAttribArray)(index))

	#undef glVertexAttribPointer
	#define glVertexAttribPointer(index, size, type, normalized, stride, pointer) GL_VERIFY(GLEW_ORIGINAL(VertexAttribPointer)(index, size, type, normalized, stride, pointer))

	#define glDrawElements(mode, count, type, indices) GL_VERIFY(glDrawElements(mode, count, type, indices))

	#undef glDisableVertexAttribArray
	#define glDisableVertexAttribArray(index) GL_VERIFY(GLEW_ORIGINAL(DisableVertexAttribArray)(index))

	#define glDisable(cap) GL_VERIFY(glDisable(cap))

	#undef glCreateShader
	#define glCreateShader(type) GL_Verify(GLEW_ORIGINAL(CreateShader)(type))

	#undef glShaderSource
	#define glShaderSource(shader, count, string, length) GL_VERIFY(GLEW_ORIGINAL(ShaderSource)(shader, count, string, length))

	#undef glCompileShader
	#define glCompileShader(shader) GL_VERIFY(GLEW_ORIGINAL(CompileShader)(shader))

	#undef glGetShaderiv
	#define glGetShaderiv(shader, pname, params) GL_VERIFY(GLEW_ORIGINAL(GetShaderiv)(shader, pname, params))

	#undef glGetShaderInfoLog
	#define glGetShaderInfoLog(shader, maxLength, length, infoLog) GL_VERIFY(GLEW_ORIGINAL(GetShaderInfoLog)(shader, maxLength, length, infoLog))

	#undef glDeleteShader
	#define glDeleteShader(shader) GL_VERIFY(GLEW_ORIGINAL(DeleteShader)(shader))

	#undef glLinkProgram
	#define glLinkProgram(program) GL_VERIFY(GLEW_ORIGINAL(LinkProgram)(program))

	#undef glGetProgramiv
	#define glGetProgramiv(program, pname, params) GL_VERIFY(GLEW_ORIGINAL(GetProgramiv)(program, pname, params))

	#undef glGetProgramInfoLog
	#define glGetProgramInfoLog(program, maxLength, length, infoLog) GL_VERIFY(GLEW_ORIGINAL(GetProgramInfoLog)(program, maxLength, length, infoLog))

	#undef glDeleteProgram
	#define glDeleteProgram(program) GL_VERIFY(GLEW_ORIGINAL(DeleteProgram)(program))

	#undef glCreateProgram
	#define glCreateProgram() GL_Verify(GLEW_ORIGINAL(CreateProgram)())

	#undef glAttachShader
	#define glAttachShader(program, shader) GL_VERIFY(GLEW_ORIGINAL(AttachShader)(program, shader))

	#undef glGetAttribLocation
	#define glGetAttribLocation(program, name) GL_Verify(GLEW_ORIGINAL(GetAttribLocation)(program, name))

	#undef glGetUniformLocation
	#define glGetUniformLocation(program, name) GL_Verify(GLEW_ORIGINAL(GetUniformLocation)(program, name))

	#undef glUniformMatrix4fv
	#define glUniformMatrix4fv(location, count, transpose, value) GL_VERIFY(GLEW_ORIGINAL(UniformMatrix4fv)(location, count, transpose, value))

	#undef glUniform1i
	#define glUniform1i(location, v0) GL_VERIFY(GLEW_ORIGINAL(Uniform1i)(location, v0))

	#undef glUseProgram
	#define glUseProgram(program) GL_VERIFY(GLEW_ORIGINAL(UseProgram)(program))

	#define glClearColor(r, g, b, a)  GL_VERIFY(glClearColor(r, g, b, a))

	#define glClear(mask) GL_VERIFY(glClear(mask))

	#define glViewport(x, y, width, height) GL_VERIFY(glViewport(x, y, width, height))

	#if defined(WIN32)
		#define glewInit() GLEW_Verify(glewInit()) 
	#endif

#endif