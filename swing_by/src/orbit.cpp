#include "orbit.h"
#include "screen.h"
#include "image.h"
#include "DxLib.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////
CrossTarget::CrossTarget(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetCrossPosition> &map) {
	this->z_sort = 90000;
	this->size = Size(64, 64);
	for (int i = 0; i < 3; ++i)this->target_spin[i] = 0.000000;

	this->player = player;
	this->mouse_pointer = mouse_pointer;
	this->map = map;
}

void CrossTarget::initialize() {
	for (int i = 0; i < 3; ++i)this->target_spin[i] = 0.000000;
}

void CrossTarget::update() {
	this->position = this->map->getCrossPosition(this->player->getPosition(), this->mouse_pointer->getPosition());

	this->target_spin[0] += M_PI / 30;
	this->target_spin[0] -= M_PI / 50;
	for (int i = 0; i < 2; ++i) {
		if (this->target_spin[i] < 0) this->target_spin[i] += M_PI * 2;
		if (this->target_spin[i] > M_PI * 2) this->target_spin[i] -= M_PI * 2;
	}

	Screen::addDrawObjectMutable(this->shared_from_this());
}

void CrossTarget::draw() const {
	for (int i = 0; i < 3; ++i) Screen::drawMutable(this->position, this->size, Image::getCrossTarget(i), 1.0, this->target_spin[i], false, 1.0);
}

void CrossTarget::finalize() {

}
////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////
OrbitPoint::OrbitPoint() {

}

void OrbitPoint::initialize() {

}

void OrbitPoint::update() {

}

void OrbitPoint::draw() const {

}

void OrbitPoint::finalize() {

}
////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////
Orbit::Orbit(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetCrossPosition> &map) {
	this->player = player;
	this->mouse_pointer = mouse_pointer;
	this->crossTarget = std::make_shared<CrossTarget>(player, mouse_pointer, map);
}

void Orbit::initialize() {
	this->line.clear();
	this->orbit.clear();
}

void Orbit::update() {
	if (this->mouse_pointer->getPosition().x < 0) return;
	if (this->mouse_pointer->getPosition().y < 0) return;
	if (this->mouse_pointer->getPosition().x > Screen::getWindowSize().width) return;
	if (this->mouse_pointer->getPosition().y > Screen::getWindowSize().height) return;

	this->crossTarget->update();
}

void Orbit::finalize() {

}
////////////////////////////////////////////////////////////////////////////////////////////////////////