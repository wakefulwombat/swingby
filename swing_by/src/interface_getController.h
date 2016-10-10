#pragma once

#include "base_internalObjectControllerBase.h"
#include "base_externalObjectControllerBase.h"
#include "base_objectBase.h"
#include <memory>

class IGetController {
public:
	virtual ~IGetController(){}
	virtual std::shared_ptr<InternalObjectController> getInternalMoveObjectController_None() = 0;
	virtual std::shared_ptr<InternalObjectController> getInternalMoveObjectController_GoStraight(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop) = 0;
	virtual std::shared_ptr<InternalObjectController> getInternalMoveObjectController_Ellipse(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, Point start_pos, Point clicked_pos, Point start_vel) = 0;
};