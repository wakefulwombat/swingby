#pragma once

#include "base_internalObjectControllerBase.h"
#include "base_externalObjectControllerBase.h"
#include "base_objectBase.h"
#include <memory>

class IGetController {
public:
	virtual ~IGetController(){}
	virtual std::unique_ptr<InternalObjectController> getInternalMoveObjectController_GoStraight(ObjectBase* obj, MoveObjectProperty* prop) = 0;
};