#pragma once

#include "common.h"

class IGetCrossPosition {
public:
	virtual ~IGetCrossPosition(){}
	virtual Point getCrossPosition(Point line_p1, Point line_p2) = 0;
};