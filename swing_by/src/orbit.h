#pragma once

#include "common.h"
#include "base_objectBase.h"
#include "interface_getCrossPosition.h"
#include <vector>
#include <memory>

class CrossTarget : public ObjectBase {
private:
	double target_spin[3];

	std::shared_ptr<ObjectBase> player;
	std::shared_ptr<ObjectBase> mouse_pointer;
	std::shared_ptr<IGetCrossPosition> map;

public:
	CrossTarget(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetCrossPosition> &map);
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};

class Orbit : public ObjectBase {
private:
	std::shared_ptr<ObjectBase> mouse_pointer;
	std::shared_ptr<ObjectBase> player;
	std::shared_ptr<MoveObjectProperty> pl_vel;

	double ell_a, ell_b, ell_e;
	Point ell_center_pos;
	Point ell_start_pos, ell_start_vel, ell_f_pos;
	double ell_rotate_rad;

	Point spin(Point pos, Point center, double rad);

public:
	Orbit(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<MoveObjectProperty> &pl_vel, const std::shared_ptr<ObjectBase> &mouse_pointer);
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;

	std::vector<Point> getNavigationPoints(Point player_pos, Point player_vel, Point mouse_pos);
	void resetParams(Point player_pos, Point player_vel, Point mouse_world_pos);
};

class OrbitManager : public RequiredFunc{
private:
	std::shared_ptr<CrossTarget> crossTarget;
	std::shared_ptr<Orbit> orbit;

	std::shared_ptr<ObjectBase> mouse_pointer;

public:
	OrbitManager(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<MoveObjectProperty> &pl_vel, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetCrossPosition> &map);
	void initialize() override;
	void update() override;
	void finalize() override;
};