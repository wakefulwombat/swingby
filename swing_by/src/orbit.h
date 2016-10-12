#pragma once

#include "common.h"
#include "base_objectBase.h"
#include "interface_getMapCrossPosition.h"
#include "interface_getOrbit.h"
#include "screen.h"
#include <vector>
#include <memory>

class CrossTarget : public ObjectBase, public std::enable_shared_from_this<CrossTarget> {
private:
	double target_spin[3];

	std::shared_ptr<ObjectBase> player;
	std::shared_ptr<ObjectBase> mouse_pointer;
	std::shared_ptr<IGetMapCrossPosition> map;

public:
	CrossTarget(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetMapCrossPosition> &map);
	void initialize() override;
	void update() override;
	void draw() const override;
	void addDraw() override { Screen::addDrawObjectMutable(this->shared_from_this()); }
	void finalize() override;
};

class Orbit : public ObjectBase {
private:
	std::shared_ptr<ObjectBase> cross_target;
	std::shared_ptr<ObjectBase> player;
	std::shared_ptr<MoveObjectProperty> pl_vel;

	double ell_a, ell_b, ell_e, ell_r0;
	Point ell_center_pos, ell_f_pos;
	double ell_rotate_rad;

	double move_vel, total_rotate_rad;
	bool go_front, go_accele, run_circle;

	Point spin(Point pos, Point center, double rad);

public:
	Orbit(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<MoveObjectProperty> &pl_vel, const std::shared_ptr<ObjectBase> &cross_target);
	void initialize() override;
	void update() override;
	void draw() const override;
	void addDraw() override { for (Point p : this->getNavigationPoints(this->player->getPosition(), this->pl_vel->getTransVelVec(), this->cross_target->getPosition())) { std::shared_ptr<Debug_Point> dp = std::make_shared<Debug_Point>(p, 2, Color(255, 130, 0), 9999); dp->update(); } }
	void finalize() override;

	std::vector<Point> getNavigationPoints(Point player_pos, Point player_vel, Point cross_target);
	
	void resetParams(Point under_f_pos, Point under_f_vel, Point f_pos);
	Point getNextVelocityVector(Point now);
};

class OrbitManager : public RequiredFunc, public IGetOrbit{
private:
	std::shared_ptr<CrossTarget> crossTarget;
	std::shared_ptr<Orbit> orbit;

	std::shared_ptr<ObjectBase> mouse_pointer;

public:
	OrbitManager(const std::shared_ptr<ObjectBase> &player, const std::shared_ptr<MoveObjectProperty> &pl_vel, const std::shared_ptr<ObjectBase> &mouse_pointer, const std::shared_ptr<IGetMapCrossPosition> &map);
	void initialize() override;
	void update() override;
	void finalize() override;

	void addDraw(){ this->crossTarget->addDraw(); this->orbit->addDraw(); }

	void resetOrbitParams(Point player_pos, Point player_vel, Point target_pos) override;
	Point getOrbitNextVelocityVector(Point player_now_pos) override;

	std::shared_ptr<ObjectBase> getCrossTarget() { return this->crossTarget; }

};