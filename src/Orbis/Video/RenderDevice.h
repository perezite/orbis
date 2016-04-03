#pragma once

#include "GraphicsAdapter.h"

#include "..\Math\Vector2D.h"
using namespace Math;

namespace Video
{
	class RenderDevice
	{
	public:
		// constructor
		RenderDevice() { };
		
		// destructor
		virtual ~RenderDevice() { };

		// begin primitive
		void BeginPrimitive(RenderMode renderMode);

		// end primitive
		void EndPrimitive();

		// set vertex 2d
		void SetVertex2D(Vector2D position);
	};
}