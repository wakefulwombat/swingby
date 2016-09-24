#pragma once

#include "base_objectBase.h"
#include "common.h"

class MousePointer : public ObjectBase {
private:
	bool move_rocked;

	Point rock_moveStart, rock_moveEnd;
	double rock_movePixel, rock_moveAngle;

public:
	MousePointer();
	void update() override;
	void draw() const override;

	void moveMousePointer(Point start, Point end, double move_pixel);
	void hide() { this->validation = false; }
	void show() { this->validation = true; }
};