#pragma once

#include "base_sceneInGameMainBase.h"

class SceneGameMainResult : public SceneInGameMainBase {
private:

public:
	SceneGameMainResult(std::shared_ptr<ISetNextSceneInGameMain> &isetNextScene);
	void initialize() override;
	void update() override;
	void finalize() override;
};