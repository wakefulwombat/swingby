#pragma once

#include "base_objectBase.h"
#include "interface_getController.h"

class Player : public ObjectBase, public AnimationObjectProperty, public MoveObjectProperty {
private:
	IGetController* ctrl_mgr;

public:
	Player(IGetController* ctrl_mgr);
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};