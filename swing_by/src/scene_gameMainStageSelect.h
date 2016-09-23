#pragma once

#include "base_sceneInGameMainBase.h"

class SceneGameMainStageSelect : public SceneInGameMainBase {
private:

public:
	SceneGameMainStageSelect(ISetNextSceneInGameMain* isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;
};