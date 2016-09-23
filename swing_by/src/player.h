#pragma once

#include "base_objectBase.h"
#include "interface_getController.h"

class Player : public ObjectBase, public AnimationObjectProperty, public MoveObjectProperty {
private:
	IGetController* controller;

public:
	Player();
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};