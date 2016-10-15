#include "timer.h"
#include "image.h"
#include "DxLib.h"

Timer::Timer() {
	this->start_time = GetNowCount();
	this->position = Point(Screen::getWindowSize().width - 90, 20);
	this->size = Size(30, 30);
	this->expansion = 0.5;
	this->z_sort = 98;
	this->validation - true;
}

void Timer::update() {
	if (!this->validation) return;

	int delta_ms = GetNowCount() - this->start_time;

	for (int i = 0; i < 5; ++i) {
		this->time[i] = (int)(delta_ms / pow(10, 5 - i));
		delta_ms -= this->time[i] * (int)pow(10, 5 - i);
	}

	this->addDraw();
}

void Timer::draw() const {
	Screen::drawOnWindow(this->position, this->size, Image::getNumber(this->time[0]), this->expansion, 0.0, 1.0);
	Screen::drawOnWindow(Point(this->position.x + 15.0,this->position.y), this->size, Image::getNumber(this->time[1]), this->expansion, 0.0, 1.0);
	Screen::drawOnWindow(Point(this->position.x + 30.0, this->position.y), this->size, Image::getNumber(this->time[2]), this->expansion, 0.0, 1.0);
	Screen::drawOnWindow(Point(this->position.x + 45.0, this->position.y), this->size, Image::getDot(), this->expansion, 0.0, 1.0);
	Screen::drawOnWindow(Point(this->position.x + 60.0, this->position.y), this->size, Image::getNumber(this->time[3]), this->expansion, 0.0, 1.0);
	Screen::drawOnWindow(Point(this->position.x + 75.0, this->position.y), this->size, Image::getNumber(this->time[4]), this->expansion, 0.0, 1.0);
}