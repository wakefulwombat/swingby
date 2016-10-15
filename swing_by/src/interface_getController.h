#pragma once

#include "base_internalObjectControllerBase.h"
#include "base_externalObjectControllerBase.h"
#include "base_objectBase.h"
#include "interface_getOrbit.h"
#include <memory>

class IGetController {
public:
	virtual ~IGetController(){}
	virtual std::shared_ptr<InternalObjectController> getInternalMoveObjectController_None() = 0;
	virtual std::shared_ptr<InternalObjectController> getInternalMoveObjectController_GoStraight(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop) = 0;
	virtual std::shared_ptr<InternalObjectController> getInternalMoveObjectController_Ellipse(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, const std::shared_ptr<IGetOrbit> &orbit, Point target_pos) = 0;
	virtual std::shared_ptr<InternalObjectController> getInternalMoveObjectController_ChargeStop(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, Point start_vel) = 0;
	virtual std::shared_ptr<InternalObjectController> getInternalMoveObjectController_OverShoot(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, double vel_target, const std::shared_ptr<IGetOrbit> &orbit) = 0;
};