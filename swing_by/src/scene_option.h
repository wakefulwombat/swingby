#pragma once

#include "base_sceneBase.h"

class SceneOption : public SceneBase {
private:

public:
	SceneOption(std::function<void(SceneKind)> changer);
	void initialize() override;
	void update() override;
	void finalize() override;
};