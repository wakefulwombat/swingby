#pragma once

#include "base_sceneInGameMainBase.h"

class SceneGameMainStageSelect : public SceneInGameMainBase {
private:

public:
	SceneGameMainStageSelect(std::shared_ptr<ISetNextSceneInGameMain> &isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;
};