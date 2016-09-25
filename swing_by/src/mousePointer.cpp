#include "mousePointer.h"
#include "input.h"
#include "screen.h"
#include "image.h"
#include <math.h>

MousePointer::MousePointer() {
	this->z_sort = 100000;
	this->move_rocked = false;
	this->size = Size(32, 32);
}

void MousePointer::update() {
	if (this->validation == false) return;

	if (this->move_rocked) {
		this->position.x = this->rock_moveStart.x + this->rock_movePixel*cos(this->rock_moveAngle);
		this->position.y = this->rock_moveStart.x + this->rock_movePixel*cos(this->rock_moveAngle);
		if (this->position.getDistance(this->rock_moveEnd) < this->rock_movePixel) {
			this->move_rocked = false;
			this->position = this->rock_moveEnd;
		}
		Input::setNowMousePoint(this->position);
	}
	else {
		this->position = Input::getNowMousePoint();
	}

	this->count++;
	Screen::addDrawObjectWindow(this);
}

void MousePointer::draw() const {
	if (this->validation == false) return;

	Screen::drawOnWindowForMouse(this->position, Image::getMousePointer(), this->img_opacity);
}

void MousePointer::moveMousePointer(Point start, Point end, double move_pixel) {
	this->move_rocked = true;
	this->rock_moveStart = start;
	this->rock_moveEnd = end;
	this->rock_movePixel = move_pixel;
	this->rock_moveAngle = atan2(this->rock_moveEnd.y - this->rock_moveStart.y, this->rock_moveEnd.x - this->rock_moveStart.x);
	this->count = 0;
}