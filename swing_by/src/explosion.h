#pragma once

#include "base_objectBase.h"
#include "base_objectManagerBase.h"
#include <memory>

class Explosion : public ObjectBase, public AnimationObjectProperty, public std::enable_shared_from_this<Explosion> {
private:

public:
	Explosion(Point pos);
	void initialize() override {}
	void update() override;
	void draw() const override;
	void addDraw() override { Screen::addDrawObjectMutable(this->shared_from_this()); }
	void finalize() override {}
};

class ExplosionManager : public ObjectManagerBase<Explosion> {
private:

public:
	void setExplosion(Point pos) { this->obj_list.push_back(std::make_shared<Explosion>(pos)); }
};