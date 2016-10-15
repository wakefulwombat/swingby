#pragma once

#include "base_sceneBase.h"

class SceneEnding : public SceneBase {
private:

public:
	SceneEnding(std::function<void(SceneKind)> changer);
	void initialize() override;
	void update() override;
	void finalize() override;
};