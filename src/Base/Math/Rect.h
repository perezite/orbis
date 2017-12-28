#pragma once

#include "Vector2D.h"

namespace Math
{
	// a struct representing a rectangle
	struct Rect
	{
	public:
		// ctor
		Rect() : leftBottom(), rightTop() {}

		// ctor
		Rect(float left, float bottom, float right, float top) 
			: leftBottom(left, bottom), rightTop(right, top)
		{}

		// ctor
		Rect(Vector2D leftBottom_, Vector2D rightTop_)
			: leftBottom(leftBottom_), rightTop(rightTop_)
		{}

		// get the left top corner
		Vector2D GetLeftTop() const { return Vector2D(leftBottom.x, rightTop.y); }

		// get the right bottom corner
		Vector2D GetRightBottom() const { return Vector2D(rightTop.x, leftBottom.y); }

		// get the width of the rect
		float GetWidth() const { return rightTop.x - leftBottom.x; }

		// get the height of the rect
		float GetHeight() const { return rightTop.y - leftBottom.y; }

		// get the area
		float GetArea() const { return GetWidth() * GetHeight(); }
	public:
		// the left bottom corner
		Vector2D leftBottom;

		// the right top corner
		Vector2D rightTop;
	};
}