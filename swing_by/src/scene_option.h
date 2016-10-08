#pragma once

#include "base_sceneBase.h"

class SceneOption : public SceneBase {
private:

public:
	SceneOption(const std::shared_ptr<ISetNextScene> &isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;
};