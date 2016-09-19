#pragma once

#include "base_objectBase.h"

class Player : public ObjectBase, public AnimationObjectProperty, public MoveObjectProperty {
private:

public:
	Player();
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};