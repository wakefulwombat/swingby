#pragma once

#include "interface_getController.h"
#include <memory>

class ControllerFactory : public IGetController{
private:

public:
	std::unique_ptr<InternalObjectController> getInternalMoveObjectController_None() override;
	std::unique_ptr<InternalObjectController> getInternalMoveObjectController_GoStraight(ObjectBase* obj, MoveObjectProperty* prop) override;
	std::unique_ptr<InternalObjectController> getInternalMoveObjectController_Ellipse(ObjectBase* obj, MoveObjectProperty* prop, Point start_pos, Point clicked_pos, Point start_vel) override;
};