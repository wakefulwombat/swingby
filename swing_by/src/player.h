#pragma once

#include "base_objectBase.h"
#include "interface_getController.h"
#include <memory>

class Player : public ObjectBase, public AnimationObjectProperty, public MoveObjectProperty {
private:
	std::shared_ptr<IGetController> ctrl_mgr;
	std::shared_ptr<ObjectBase> mouse_pointer;

public:
	Player(const std::shared_ptr<IGetController> &ctrl_mgr, const std::shared_ptr<ObjectBase> &mouse_pointer);
	void initialize() override {}
	void update() override;
	void draw() const override;
	void finalize() override;

	void initialize(Point start);
};