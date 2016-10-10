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
InternalMoveObjectController_Ellipse::InternalMoveObjectController_Ellipse(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, Point start_pos, Point clicked_pos, Point start_vel) {
	this->obj = obj;
	this->prop = prop;
	this->start_pos = start_pos;
	this->clicked_pos = clicked_pos;
	this->start_vel = start_vel;
}

void InternalMoveObjectController_Ellipse::update() {
	
}

void InternalMoveObjectController_Ellipse::end() {
	this->obj->setControlRights(ControlStatus::Movable);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////