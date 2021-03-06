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
};

class InternalMoveObjectController_GoStraight : public InternalObjectController {
private:
	std::shared_ptr<ObjectBase> obj;
	std::shared_ptr<MoveObjectProperty> prop;
public:
	InternalMoveObjectController_GoStraight(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop);
	void update() override;
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
};

class InternalMoveObjectController_ChargeStop : public InternalObjectController {
private:
	std::shared_ptr<ObjectBase> obj;
	std::shared_ptr<MoveObjectProperty> prop;
	int count;
	Point start_vel;

	Point mouse_pos;

public:
	InternalMoveObjectController_ChargeStop(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, Point start_vel);
	void update() override;
};

class InternalMoveObjectController_OverShoot : public InternalObjectController {
private:
	std::shared_ptr<ObjectBase> obj;
	std::shared_ptr<MoveObjectProperty> prop;
	std::shared_ptr<IGetOrbit> orbit;
	int count;
	double vel_target, vel_now;
	double omega, zeta;

	double c(int t);

public:
	InternalMoveObjectController_OverShoot(const std::shared_ptr<ObjectBase> &obj, const std::shared_ptr<MoveObjectProperty> &prop, double vel_target, const std::shared_ptr<IGetOrbit> &orbit);
	void update() override;
	bool isEnd() override;
};