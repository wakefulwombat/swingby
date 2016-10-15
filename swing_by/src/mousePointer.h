#pragma once

#include "base_objectBase.h"
#include "common.h"
#include "screen.h"
#include "interface_setMousePointer.h"

class MousePointer : public ObjectBase, public std::enable_shared_from_this<MousePointer>, public ISetMousePointer {
private:
	bool move_rocked;

	Point rock_moveStart, rock_moveEnd;
	double rock_movePixel, rock_moveAngle;

	Point remember_pos;

public:
	MousePointer();
	void update() override;
	void draw() const override;
	void addDraw() override { Screen::addDrawObjectWindow(this->shared_from_this()); }

	void moveMousePointer(Point start, Point end, double move_pixel) override;
	void hide() override { this->validation = false; }
	void show() override { this->validation = true; }
	void rememberHide() override;
	void rememberShow() override;
};