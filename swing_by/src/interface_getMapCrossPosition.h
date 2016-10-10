#pragma once

#include "common.h"

class IGetMapCrossPosition {
public:
	virtual ~IGetMapCrossPosition(){}
	virtual Point getMapCrossPosition(Point line_p1, Point line_p2) = 0;
};