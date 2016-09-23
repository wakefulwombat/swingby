#include "controllerFactory.h"
#include "controller.h"

std::unique_ptr<InternalObjectController> ControllerFactory::getInternalMoveObjectController_GoStraight(ObjectBase* obj, MoveObjectProperty* prop) {
	return std::unique_ptr<InternalObjectController>(new InternalMoveObjectController_GoStraight(obj, prop));
}