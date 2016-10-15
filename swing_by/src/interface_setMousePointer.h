#pragma once

#include "common.h"

class ISetMousePointer {
public:
	virtual ~ISetMousePointer(){}
	virtual void moveMousePointer(Point start, Point end, double move_pixel) = 0;
	virtual void hide() = 0;
	virtual void show() = 0;
	virtual void rememberHide() = 0;
	virtual void rememberShow() = 0;
};