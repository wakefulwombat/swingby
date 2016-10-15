#include "player.h"
#include "input.h"
#include "image.h"
#include <math.h>

Player::Player() {
	this->count = 0;

	this->control_status = ControlStatus::None;
	this->z_sort = 100;
	this->size = Size(56, 24);
	this->position = Point();

	this->chip_count = 0;
	this->chip_switch_time = 10;
	this->show_chip_index = 0;

	this->trans_vel = 2.0;
	this->trans_rad = 0.000000;
}

void Player::initialize(Point start) {
	this->count = 0;
	this->ctrl_mgr = ctrl_mgr;
	this->control_status = ControlStatus::InternalControlled;
	this->internalController = this->ctrl_mgr->getInternalMoveObjectController_None();
	this->z_sort = 100;
	this->size = Size(56, 24);
	this->position = start;

	this->chip_count = 0;
	this->chip_switch_time = 10;
	this->show_chip_index = 0;
	Screen::initTargetPositionDeltaCenter(Point(-200.0, 0.0));
}

void Player::update() {
	if (!this->validation) return;

	this->internalController->update();
	this->vector_trans_timer->update();

	if (Input::getKeyCodeDownOnce(KeyType::Game_Swing_OK)) {
		if(this->internalController->isEnd()) this->internalController = this->ctrl_mgr->getInternalMoveObjectController_Ellipse(this->shared_from_this(), this->shared_from_this(), this->orbit, this->cross_target->getPosition());
	}
	if (Input::getKeyCodeUpOnce(KeyType::Game_Swing_OK)) {
		if (this->internalController->isEnd()) this->internalController = this->ctrl_mgr->getInternalMoveObjectController_GoStraight(this->shared_from_this(), this->shared_from_this());
	}

	if (Input::getKeyCodeDownOnce(KeyType::Game_VectorTrans_CANCEL)) {
		if (this->internalController->isEnd()&&!this->vector_trans_timer->getValidation()) {
			this->overshoot_vel = this->trans_vel;
			this->internalController = this->ctrl_mgr->getInternalMoveObjectController_ChargeStop(this->shared_from_this(), this->shared_from_this(), this->getTransVelVec());
			this->mouse_pointer->rememberHide();
		}
	}
	if (Input::getKeyCodeUpOnce(KeyType::Game_VectorTrans_CANCEL)) {
		if (this->internalController->isEnd()) {
			this->vector_trans_timer->restart();
			this->internalController = this->ctrl_mgr->getInternalMoveObjectController_OverShoot(this->shared_from_this(), this->shared_from_this(), this->overshoot_vel);
			this->mouse_pointer->rememberShow();
		}
	}
	if (Input::getKeyCodeDown(KeyType::Game_VectorTrans_CANCEL)) {

	}

	this->count++;
	this->chip_count++;
	if (this->chip_count%this->chip_switch_time == 0) this->show_chip_index = (this->show_chip_index + 1) % 2;
	this->addDraw();

	Screen::setTargetWorldPosition(this->position, 30);
}

void Player::draw() const {
	Screen::drawMutable(this->position, this->size, Image::getPlayer(this->show_chip_index), this->expansion, this->img_rotation, false, this->img_opacity);
}

void Player::finalize() {

}

void Player::setInterface(const std::shared_ptr<IGetController> &ctrl_mgr, const std::shared_ptr<ObjectBase> &cross_target, const std::shared_ptr<IGetOrbit> &orbit, const std::shared_ptr<ISetMousePointer> &mouse_pointer) {
	this->ctrl_mgr = ctrl_mgr;
	this->cross_target = cross_target;
	this->orbit = orbit;
	this->mouse_pointer = mouse_pointer;

	this->vector_trans_timer = std::make_shared<TimerRing>(this->shared_from_this(), 300);

	this->control_status = ControlStatus::InternalControlled;
	this->internalController = this->ctrl_mgr->getInternalMoveObjectController_None();
}