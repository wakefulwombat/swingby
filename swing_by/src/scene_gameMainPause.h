#pragma once

#include "base_sceneBase.h"

class SceneGameMainPause : public SceneBase {
private:

public:
	SceneGameMainPause(const std::shared_ptr<ISetNextScene> &isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;
};