#include "explosion.h"
#include "screen.h"
#include "image.h"

Explosion::Explosion(Point pos) {
	this->position = pos;
	this->chip_count = 0;
	this->chip_switch_time = 5;
	this->chipSize = 14;
	this->expansion = 1.0;
	this->img_opacity = 0.7;
	this->repeat = false;
	this->show_chip_index = 0;
	this->size = Size(240, 240);
	this->validation = true;
	this->z_sort = 5000;
}

void Explosion::update() {
	if (this->validation == false) return;

	this->chip_count++;
	if (this->chip_count%this->chip_switch_time == 0) this->show_chip_index++;
	if (this->show_chip_index == this->chipSize) this->validation = false;

	Screen::addDrawObjectMutable(this->shared_from_this());
}

void Explosion::draw() const {
	Screen::drawMutable(this->position, this->size, Image::getExplosion(this->show_chip_index), this->expansion, 0.0, false, this->img_opacity);
}