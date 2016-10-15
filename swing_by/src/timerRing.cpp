#include "timerRing.h"

TimerRing::TimerRing(const std::shared_ptr<ObjectBase> &obj, int end_time) {
	this->obj = obj;
	this->end_time = end_time;
	this->z_sort = 99;

	this->validation = false;
}

void TimerRing::update() {
	if (!this->validation) return;

	this->count++;
	if (this->count == this->end_time) this->validation = false;

	this->position = this->obj->getPosition();

	this->addDraw();
}

void TimerRing::draw() const {
	if (this->count < this->end_time*0.1) Screen::drawPoint(this->position, (int)(100 * this->count / (this->end_time*0.1)), Color(0, 255, 50), false);
	else Screen::drawPoint(this->position, (int)(100 * (1.0 - 1.0*(this->count - this->end_time*0.1) / (this->end_time*0.9))), Color(0, 255, 50), false);
}

void TimerRing::restart() {
	this->count = 0;
	this->validation = true;
}