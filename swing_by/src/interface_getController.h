#pragma once

#include "base_internalObjectControllerBase.h"
#include "base_externalObjectControllerBase.h"
#include "base_objectBase.h"
#include <memory>

class IGetController {
public:
	virtual ~IGetController(){}
	virtual std::unique_ptr<InternalObjectController> getInternalMoveObjectController_None() = 0;
	virtual std::unique_ptr<InternalObjectController> getInternalMoveObjectController_GoStraight(ObjectBase* obj, MoveObjectProperty* prop) = 0;
	virtual std::unique_ptr<InternalObjectController> getInternalMoveObjectController_Ellipse(ObjectBase* obj, MoveObjectProperty* prop, Point start_pos, Point clicked_pos, Point start_vel) = 0;
};