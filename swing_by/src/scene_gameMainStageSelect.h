#pragma once

#include "base_sceneInGameMainBase.h"

class SceneGameMainStageSelect : public SceneInGameMainBase {
private:

public:
	SceneGameMainStageSelect(std::function<void(SceneInGameMainKind)> sceneChanger);
	void initialize() override;
	void update() override;
	void finalize() override;
};