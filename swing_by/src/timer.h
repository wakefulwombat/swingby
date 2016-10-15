#pragma once

#include "base_objectBase.h"
#include "screen.h"
#include <memory>

class Timer : public ObjectBase, public std::enable_shared_from_this<Timer> {
private:
	int start_time;
	int time[5];

public:
	Timer();
	void update() override;
	void draw() const override;
	void addDraw() override { Screen::addDrawObjectWindow(this->shared_from_this()); }
};