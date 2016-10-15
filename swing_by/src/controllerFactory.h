#pragma once

#include "interface_getController.h"
#include <memory>

class ControllerFactory : public IGetController{
private:

public:
	std::shared_ptr<InternalObjectController> getInternalMoveObjectController_None() override;
	std::shared_ptr<InternalObjectController> getInternalMoveObjectController_GoStraight(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop) override;
	std::shared_ptr<InternalObjectController> getInternalMoveObjectController_Ellipse(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, const std::shared_ptr<IGetOrbit> &orbit, Point target_pos) override;
	std::shared_ptr<InternalObjectController> getInternalMoveObjectController_ChargeStop(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, Point start_vel) override;
	std::shared_ptr<InternalObjectController> getInternalMoveObjectController_OverShoot(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, double vel_target, const std::shared_ptr<IGetOrbit> &orbit) override;
};