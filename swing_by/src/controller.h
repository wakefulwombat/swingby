#pragma once

#include "base_internalObjectControllerBase.h"
#include "base_externalObjectControllerBase.h"
#include "base_objectBase.h"

class InternalMoveObjectController_GoStraight : public InternalObjectController {
private:
	ObjectBase* obj;
	MoveObjectProperty* prop;
public:
	InternalMoveObjectController_GoStraight(ObjectBase* obj, MoveObjectProperty* prop);
	void update() override;
	void end() override;
};