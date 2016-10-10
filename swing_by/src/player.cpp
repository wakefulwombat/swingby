#include "player.h"
#include "input.h"
#include "screen.h"
#include "image.h"
#include <math.h>

Player::Player(const std::shared_ptr<IGetController> &ctrl_mgr, const std::shared_ptr<ObjectBase> &mouse_pointer) {
	this->count = 0;
	this->ctrl_mgr = ctrl_mgr;
	this->mouse_pointer = mouse_pointer;
	this->control_status = ControlStatus::InternalControlled;
	this->internalController = this->ctrl_mgr->getInternalMoveObjectController_None();
	this->z_sort = 5000;
	this->size = Size(56, 24);
	this->position = Point();

	this->chip_count = 0;
	this->chip_switch_time = 10;
	this->show_chip_index = 0;

	this->trans_vel = 1.0;
	this->trans_rad = 0.000000;
}

void Player::initialize(Point start) {
	this->count = 0;
	this->ctrl_mgr = ctrl_mgr;
	this->control_status = ControlStatus::InternalControlled;
	this->internalController = this->ctrl_mgr->getInternalMoveObjectController_None();
	this->z_sort = 5000;
	this->size = Size(56, 24);
	this->position = start;

	this->chip_count = 0;
	this->chip_switch_time = 10;
	this->show_chip_index = 0;
	Screen::initTargetPositionDeltaCenter(Point(-200.0, 0.0));
}

void Player::update() {
	this->internalController->update();

	if (Input::getKeyCodeDownOnce(KeyType::Game_Swing_OK) == 0) {
		this->internalController = this->ctrl_mgr->getInternalMoveObjectController_Ellipse(this->shared_from_this(), this->shared_from_this(), this->position, this->mouse_pointer->getPosition(), this->getTransVelVec());
	}
	if (Input::getKeyCodeUpOnce(KeyType::Game_Swing_OK) == 0) {
		this->internalController = this->ctrl_mgr->getInternalMoveObjectController_GoStraight(this->shared_from_this(), this->shared_from_this());
	}
	if (Input::getKeyCodeDown(KeyType::Game_Swing_OK) == 0) {
		
	}

	if (Input::getKeyCodeDownOnce(KeyType::Game_VectorTrans_CANCEL) == 0) {

	}
	if (Input::getKeyCodeUpOnce(KeyType::Game_VectorTrans_CANCEL) == 0) {

	}
	if (Input::getKeyCodeDown(KeyType::Game_VectorTrans_CANCEL) == 0) {

	}

	this->count++;
	this->chip_count++;
	if (this->chip_count%this->chip_switch_time == 0) this->show_chip_index = (this->show_chip_index + 1) % 2;
	Screen::addDrawObjectMutable(this->shared_from_this());

	Screen::setTargetWorldPosition(this->position, 30);
}

void Player::draw() const {
	Screen::drawMutable(this->position, this->size, Image::getPlayer(this->show_chip_index), this->expansion, this->img_rotation, false, this->img_opacity);
}

void Player::finalize() {

}