#include "controllerFactory.h"
#include "controller.h"

std::shared_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_None() {
	return std::make_shared<InternalMoveObjectController_None>();
}

std::shared_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_GoStraight(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop) {
	return std::make_shared<InternalMoveObjectController_GoStraight>(obj, prop);
}

std::shared_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_Ellipse(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, Point start_pos, Point clicked_pos, Point start_vel){
	return std::make_shared<InternalMoveObjectController_Ellipse>(obj, prop, start_pos, clicked_pos, start_vel);
}