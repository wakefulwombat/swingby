#include "controllerFactory.h"
#include "controller.h"

std::unique_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_None() {
	return std::unique_ptr<InternalObjectController>(new InternalMoveObjectController_None());
}

std::unique_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_GoStraight(ObjectBase* obj, MoveObjectProperty* prop) {
	return std::unique_ptr<InternalObjectController>(new InternalMoveObjectController_GoStraight(obj, prop));
}

std::unique_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_Ellipse(ObjectBase* obj, MoveObjectProperty* prop, Point start_pos, Point clicked_pos, Point start_vel){
	return std::unique_ptr<InternalObjectController>(new InternalMoveObjectController_Ellipse(obj, prop, start_pos, clicked_pos, start_vel));
}