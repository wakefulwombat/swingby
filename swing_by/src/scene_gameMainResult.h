#pragma once

#include "base_sceneInGameMainBase.h"

class SceneGameMainResult : public SceneInGameMainBase {
private:

public:
	SceneGameMainResult(ISetNextSceneInGameMain* isetNextScene);
	void initialize() override;
	void update() override;
	void draw() const override;
	void finalize() override;
};