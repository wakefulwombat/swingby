#pragma once

#include "base_internalObjectControllerBase.h"
#include "base_externalObjectControllerBase.h"
#include "base_objectBase.h"
#include "interface_getOrbit.h"
#include <memory>

class InternalMoveObjectController_None : public InternalObjectController {
public:
	InternalMoveObjectController_None();
	void update() override;
	void end() override;
};

class InternalMoveObjectController_GoStraight : public InternalObjectController {
private:
	std::shared_ptr<ObjectBase> obj;
	std::shared_ptr<MoveObjectProperty> prop;
public:
	InternalMoveObjectController_GoStraight(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop);
	void update() override;
	void end() override;
};

class InternalMoveObjectController_Ellipse : public InternalObjectController {
private:
	Point start_pos, clicked_pos, start_vel;
	std::shared_ptr<ObjectBase> obj;
	std::shared_ptr<MoveObjectProperty> prop;
	std::shared_ptr<IGetOrbit> orbit;
public:
	InternalMoveObjectController_Ellipse(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, const std::shared_ptr<IGetOrbit> &orbit, Point target_pos);
	void update() override;
	void end() override;
};