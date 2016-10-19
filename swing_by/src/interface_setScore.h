#pragma once

class ISetScore {
public:
	virtual void setNowSpeed(double now_speed) = 0;
	virtual void addSwingCount() = 0;
};