#pragma once

#include "base_sceneInGameMainBase.h"

class SceneGameMainStage : public SceneInGameMainBase {
private:

public:
	SceneGameMainStage(ISetNextSceneInGameMain* isetNextScene);
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};