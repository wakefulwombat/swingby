#pragma once

class ISetScore {
public:
	virtual void setGoalTime(double goal_time) = 0;
	virtual void setNowSpeed(double now_speed) = 0;
	virtual void setGoalSpeed(double goal_speed) = 0;
	virtual void addSwingCound() = 0;
};