#pragma once

#include "base_internalObjectControllerBase.h"
#include "base_externalObjectControllerBase.h"
#include "base_objectBase.h"

class InternalMoveObjectController_None : public InternalObjectController {
public:
	InternalMoveObjectController_None();
	void update() override;
	void end() override;
};

class InternalMoveObjectController_GoStraight : public InternalObjectController {
private:
	ObjectBase* obj;
	MoveObjectProperty* prop;
public:
	InternalMoveObjectController_GoStraight(ObjectBase* obj, MoveObjectProperty* prop);
	void update() override;
	void end() override;
};

class InternalMoveObjectController_Ellipse : public InternalObjectController {
private:
	Point start_pos, clicked_pos, start_vel;
	ObjectBase* obj;
	MoveObjectProperty* prop;
public:
	InternalMoveObjectController_Ellipse(ObjectBase* obj, MoveObjectProperty* prop, Point start_pos, Point clicked_pos, Point start_vel);
	void update() override;
	void end() override;
};