#include "controller.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InternalMoveObjectController_None::InternalMoveObjectController_None() {}

void InternalMoveObjectController_None::update() {}

void InternalMoveObjectController_None::end() {}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InternalMoveObjectController_GoStraight::InternalMoveObjectController_GoStraight(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop) {
	this->obj = obj;
	this->prop = prop;
}

void InternalMoveObjectController_GoStraight::update() {
	this->obj->setPosition(this->obj->getPosition() + this->prop->getTransVelVec());
}

void InternalMoveObjectController_GoStraight::end() {
	this->obj->setControlRights(ControlStatus::Movable);
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

void InternalMoveObjectController_Ellipse::end() {
	this->obj->setControlRights(ControlStatus::Movable);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////