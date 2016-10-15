#pragma once

#include "base_sceneBase.h"

class SceneOpening : public SceneBase {
private:

public:
	SceneOpening(std::function<void(SceneKind)> changer);
	void initialize() override;
	void update() override;
	void finalize() override;
};