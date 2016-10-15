#include "controller.h"
#include "input.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InternalMoveObjectController_None::InternalMoveObjectController_None() {}

void InternalMoveObjectController_None::update() {}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InternalMoveObjectController_GoStraight::InternalMoveObjectController_GoStraight(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop) {
	this->obj = obj;
	this->prop = prop;
}

void InternalMoveObjectController_GoStraight::update() {
	this->obj->setPosition(this->obj->getPosition() + this->prop->getTransVelVec());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InternalMoveObjectController_Ellipse::InternalMoveObjectController_Ellipse(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, const std::shared_ptr<IGetOrbit> &orbit, Point target_pos) {
	this->obj = obj;
	this->prop = prop;
	this->orbit = orbit;

	this->orbit->resetOrbitParams(obj->getPosition(), prop->getTransVelVec(), target_pos);
}

void InternalMoveObjectController_Ellipse::update() {
	Point vel = this->orbit->getOrbitNextVelocityVector(this->obj->getPosition());
	this->obj->setImageRotationRad(atan2(vel.y, vel.x));
	this->obj->setPosition(this->obj->getPosition() + vel);
	this->prop->setTransVelVec(vel);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InternalMoveObjectController_ChargeStop::InternalMoveObjectController_ChargeStop(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, Point start_vel) {
	this->obj = obj;
	this->prop = prop;
	this->count = 0;
	this->start_vel = start_vel;

	this->mouse_pos = Input::getNowMousePoint();
}

void InternalMoveObjectController_ChargeStop::update() {
	Point vel = Point(0.2, 0.2);
	if (this->count < 60) {
		vel = this->start_vel*(1.0 - this->count / 60.0);
		this->count++;
	}
	this->prop->setTransVelVec(vel);
	this->obj->setPosition(this->obj->getPosition() + this->prop->getTransVelVec());

	this->obj->setImageRotationRad(atan2(-Input::getNowMousePoint().y + this->mouse_pos.y, -Input::getNowMousePoint().x + this->mouse_pos.x));
	if (Input::getKeyCodeUpOnce(KeyType::Game_VectorTrans_CANCEL)) this->prop->setTransRad(this->obj->getImageRotationRad());
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InternalMoveObjectController_OverShoot::InternalMoveObjectController_OverShoot(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, double vel_target) {
	this->obj = obj;
	this->prop = prop;
	this->count = 0;
	this->vel_target = vel_target;

	this->omega = M_PI * 2 / 60;
	this->vel_now = 0.0;
	this->zeta = 0.2;
}

void InternalMoveObjectController_OverShoot::update() {
	if (this->count < 60) {
		this->vel_now = this->vel_target*this->c(this->count) + 0.2;
		this->prop->setTransVelVec(Point(this->vel_now*cos(this->prop->getTransRad()), this->vel_now*sin(this->prop->getTransRad())));
		this->count++;
	}
	this->obj->setPosition(this->obj->getPosition() + this->prop->getTransVelVec());
}

bool InternalMoveObjectController_OverShoot::isEnd() {
	if (this->count == 60) return true;
	return false;
}

double InternalMoveObjectController_OverShoot::c(int t) {
	return 1.0 - 1.0 / sqrt(1 - this->zeta*this->zeta)*exp(-this->zeta*this->omega*t) * (this->zeta*sin(this->omega*sqrt(1 - this->zeta*this->zeta)*t) + sqrt(1 - this->zeta*this->zeta)*cos(this->omega*sqrt(1 - this->zeta*this->zeta)*t));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////