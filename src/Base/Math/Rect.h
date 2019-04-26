#pragma once

#include "Vector2.h"

namespace base
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
		Rect(Vector2f leftBottom_, Vector2f rightTop_)
			: leftBottom(leftBottom_), rightTop(rightTop_)
		{}

		// ctor - creates a square at the given position with the given extent
		Rect(Vector2f pos, float extent)
			: leftBottom(pos.x - extent, pos.y - extent), rightTop(pos.x + extent, pos.y + extent)
		{}

		// get the left top corner
		Vector2f getLeftTop() const { return Vector2f(leftBottom.x, rightTop.y); }

		// get the right bottom corner
		Vector2f getRightBottom() const { return Vector2f(rightTop.x, leftBottom.y); }

		// get the width of the rect
		float getWidth() const { return rightTop.x - leftBottom.x; }

		// get the height of the rect
		float getHeight() const { return rightTop.y - leftBottom.y; }

		// get the size of the rect
		const Vector2f getSize() const { return Vector2f(getWidth(), getHeight()); }

		// get the area
		float getArea() const { return getWidth() * getHeight(); }

		// get left
		float getLeft() const { return leftBottom.x; }

		// get bottom
		float getBottom() const { return leftBottom.y; }

		// get right
		float getRight() const { return rightTop.x; }

		// get top
		float getTop() const { return rightTop.y; }

		// check if rect contains point
		bool contains(Vector2f point) { return point.x >= getLeft() && point.x <= getRight() && point.y >= getBottom() && point.y <= getTop(); }

	public:
		// the left bottom corner
		Vector2f leftBottom;

		// the right top corner
		Vector2f rightTop;

		// an index, can be used to identify rects after a non order-stable algorithm was performed
		unsigned int index;
	};
}