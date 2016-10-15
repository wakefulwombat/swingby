#include "controllerFactory.h"
#include "controller.h"

std::shared_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_None() {
	return std::make_shared<InternalMoveObjectController_None>();
}

std::shared_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_GoStraight(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop) {
	return std::make_shared<InternalMoveObjectController_GoStraight>(obj, prop);
}

std::shared_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_Ellipse(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, const std::shared_ptr<IGetOrbit> &orbit, Point target_pos){
	return std::make_shared<InternalMoveObjectController_Ellipse>(obj, prop, orbit, target_pos);
}

std::shared_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_ChargeStop(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, Point start_vel) {
	return std::make_shared<InternalMoveObjectController_ChargeStop>(obj, prop, start_vel);
}

std::shared_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_OverShoot(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, double vel_target, const std::shared_ptr<IGetOrbit> &orbit) {
	return std::make_shared<InternalMoveObjectController_OverShoot>(obj, prop, vel_target, orbit);
}