#pragma once

#include "base_sceneBase.h"

class SceneEnding : public SceneBase {
private:

public:
	SceneEnding(std::shared_ptr<ISetNextScene> &isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;
};