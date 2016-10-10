#pragma once

#include "common.h"

class IGetOrbit {
public:
	virtual ~IGetOrbit() {};
	virtual void resetOrbitParams(Point player_pos, Point player_vel, Point target_pos) = 0;
	virtual Point getOrbitNextVelocityVector(Point player_now_pos) = 0;
};