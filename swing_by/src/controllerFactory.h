#pragma once

#include "interface_getController.h"
#include <memory>

class ControllerFactory : public IGetController{
private:

public:
	std::unique_ptr<InternalObjectController> getInternalMoveObjectController_GoStraight(ObjectBase* obj, MoveObjectProperty* prop) override;
};