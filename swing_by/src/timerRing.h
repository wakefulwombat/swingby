#pragma once

#include "common.h"
#include "base_objectBase.h"
#include "screen.h"
#include <memory>

class TimerRing : public ObjectBase, public std::enable_shared_from_this<TimerRing> {
private:
	std::shared_ptr<ObjectBase> obj;
	int end_time;

public:
	TimerRing(const std::shared_ptr<ObjectBase> &obj, int end_time);
	void update() override;
	void draw() const override;
	void addDraw() override { Screen::addDrawObjectMutable(this->shared_from_this()); }

	void restart();
};