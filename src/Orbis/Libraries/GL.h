#pragma once

// comment out this define to disable exceptions for GL calls
#define GL_EXCEPTIONS

namespace Libraries
{
	// wrapper class for OpenGL calls
	class GL
	{
	public:
		// clear color
		static void ClearColor(float r, float g, float b, float a);
	};
}