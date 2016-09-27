#pragma once

#include "common.h"
#include <vector>

class Orbit {
private:

public:
	std::vector<Point> getOrbitPositionList(Point start_pos, Point start_vel, Point focal_pos, int list_num);
};