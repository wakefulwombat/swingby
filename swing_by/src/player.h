#pragma once

#include "base_objectBase.h"
#include "interface_getController.h"
#include "interface_getOrbit.h"
#include "interface_setMousePointer.h"
#include "interface_setScore.h"
#include "timerRing.h"
#include "screen.h"
#include <memory>

class Player : public ObjectBase, public AnimationObjectProperty, public MoveObjectProperty, public std::enable_shared_from_this<Player> {
private:
	std::shared_ptr<IGetController> ctrl_mgr;
	std::shared_ptr<ObjectBase> cross_target;
	std::shared_ptr<IGetOrbit> orbit;
	std::shared_ptr<ISetMousePointer> mouse_pointer;
	std::shared_ptr<ISetScore> score;

	std::shared_ptr<TimerRing> vector_trans_timer;

	double overshoot_vel;

public:
	Player();
	void initialize() override {}
	void update() override;
	void draw() const override;
	void addDraw() override { Screen::addDrawObjectMutable(this->shared_from_this()); }
	void finalize() override;

	void initialize(Point start);
	void setInterface(const std::shared_ptr<IGetController> &ctrl_mgr, const std::shared_ptr<ObjectBase> &cross_target, const std::shared_ptr<IGetOrbit> &orbit, const std::shared_ptr<ISetMousePointer> &mouse_pointer, const std::shared_ptr<ISetScore> &score);
};